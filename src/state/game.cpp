#include "./game.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include "../gameplay/characters/player.h"
#include "../utils/helpers.h"
#include "../utils/loggers.h"
#include "io/key_action.h"

namespace blackjack {
Game::Game(std::unique_ptr<Player> dealer, std::unique_ptr<Deck> deck) {
  _ID = generate_uuid();
  _dealer = std::move(dealer);
  _deck = std::move(deck);
  _state = Game::States::GAMESTART;
}

void Game::start() {
  // Need to have a player.
  assert(_players.size() > 0);

  // Dealer draw once. In reality, they draw twice,
  // but unless we want to do something with second card.
  // We should be fine drawing one
  _dealer->draw(_deck.get());

  // Unneccessary, but just for testing
  for (auto& player : _players) {
    player->draw(_deck.get());
  }

  Logger::get().info(current_state());
  _state = Game::States::PLAYER_TURN;
}

void Game::add_player(std::unique_ptr<Player> player) {
  assert(_state == Game::States::GAMESTART);
  _players.push_back(std::move(player));
}

Player* Game::current_player() {
  return _players[_player_position % _players.size()].get();
}

void Game::send_action(const KeyAction::Id& action) {
  switch (_state) {
    case Game::States::DEALER_TURN:
      handle_action(_dealer.get(), action);
      break;
    case Game::States::PLAYER_TURN:
      // TODO(June): Update this to include a logic for which player it is for.
      handle_action(current_player(), action);
      break;
    default:
      break;
  }
}

void Game::dealers_turn() {
  assert(_state == Game::States::DEALER_TURN);

  int32_t dealer_total = _dealer->hand_values_ints();

  // Keep drawing until it is 16
  while (dealer_total <= 16) {
    _dealer->draw(_deck.get());
    Logger::get().info("Dealer Draws\n");
    Logger::get().info(current_state());
    dealer_total = _dealer->hand_values_ints();
  }
}

void Game::handle_action(Player* character, const KeyAction::Id& action) {
  assert(_state == Game::States::PLAYER_TURN);
  switch (action) {
    case KeyAction::Id::HIT:
      character->draw(_deck.get());
      Logger::get().info(current_state());
      // TODO(June): Update this logic when there is more than one players.
      if (blackjack_or_busted(*character) > 0) {
        if (_player_position == _players.size() - 1) {
          _state = Game::States::GAMEOVER;
          determine_winner();
        }
        // go to next player
        _player_position += 1;
        Logger::get().info(current_state());
      }
      break;
    case KeyAction::Id::STAND:
      _player_position += 1;
      if (_player_position >= _players.size()) {
        _state = Game::States::DEALER_TURN;
        dealers_turn();
        determine_winner();
        _state = Game::States::GAMEOVER;
      } else {
        Logger::get().info("Next Player " +
                           std::to_string(_player_position + 1));
        Logger::get().info(current_state());
      }
      break;
    default:
      break;
  }
}

bool Game::alive() {
  return _state != Game::States::GAMEOVER;
}

std::string Game::current_state() {
  std::string player_msg =
      _player_position < _players.size()
          ? "\nPlayer " + std::to_string(_player_position + 1) + ": " +
                std::to_string(current_player()->hand_values_ints()) + "\n"
          : "\n";

  return _ID + ":\nCurrent State:\nDealer:\t" +
         std::to_string(_dealer->hand_values_ints()) + player_msg;
}

Game::PlayerState Game::blackjack_or_busted(const Player& player) {
  const int& total = player.hand_values_ints();

  if (total < 21) {
    return Game::PlayerState::ALIVE;
  } else if (total == 21) {
    Logger::get().info("Player " + std::to_string(_player_position + 1) +
                       " WON!");
    return Game::PlayerState::BLACKJACK;
  } else {
    Logger::get().info("Player " + std::to_string(_player_position + 1) +
                       " BUSTED!");
    return Game::PlayerState::BUSTED;
  }
}

void Game::determine_winner() {
  const int& dealer_total = _dealer->hand_values_ints();
  int pos = 1;
  std::cout << "\n\n\n---------------------\n\n\n";
  for (auto& player : _players) {
    const int& player_total = player->hand_values_ints();
    std::cout << "\nFor Player " + std::to_string(pos) << "\n\n";
    if (player_total > 21) {
      std::cout << "Player busted! Dealer wins!" << "\n";
      _state = Game::States::GAMEOVER;
    } else if (dealer_total > 21) {
      std::cout << "Dealer busted! Player wins!" << "\n";
      _state = Game::States::GAMEOVER;
    } else if (player_total > dealer_total) {
      std::cout << "Player wins!" << "\n";
      _state = Game::States::GAMEOVER;
    } else if (player_total < dealer_total) {
      std::cout << "Dealer wins!" << "\n";
      _state = Game::States::GAMEOVER;
    }
    pos += 1;
  }
  std::cout << "\n\n\n---------------------\n\n\n";
}

Game::~Game() {
  Logger::get().info("DELETING GAME");
}
}  // namespace blackjack
