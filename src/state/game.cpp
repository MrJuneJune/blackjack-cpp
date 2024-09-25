#include "./game.h"
#include <cassert>
#include <iostream>
#include <string>
#include "../gameplay/characters/player.h"
#include "../utils/helpers.h"
#include "../utils/loggers.h"
#include "io/key_action.h"

namespace blackjack {
Game::Game(Player* player1, Player* dealer, Deck* deck) {
  _ID = generate_uuid();
  _players.push_back(player1);
  _dealer = dealer;
  _deck = deck;
  _state = Game::States::GAMESTART;

  // Unneccessary, but just for testing
  _players.back()->draw(_deck);

  // Dealer draw once. In reality, they draw twice, but unless we want to do something with second card **cheating**
  // We should be fine drawing one
  _dealer->draw(_deck);

  Logger::get().info(current_state());
  _state = Game::States::PLAYER_TURN;
}

void Game::send_action(const KeyAction::Id& action) {
  switch (_state) {
    case Game::States::DEALER_TURN:
      handle_action(_dealer, action);
      break;
    case Game::States::PLAYER_TURN:
      // TODO(June): Update this to include a logic for which player it is for.
      handle_action(_players.back(), action);
      break;
    default:
      break;
  }
}

void Game::dealers_turn() {
  int32_t dealer_total = _dealer->hand_values_ints();

  // Keep drawing until it is 16
  while (dealer_total <= 16) {
    _dealer->draw(_deck);
    Logger::get().info("Dealer Draws\n");
    Logger::get().info(current_state());
    dealer_total = _dealer->hand_values_ints();
  }
};

void Game::handle_action(Player* character, const KeyAction::Id& action) {
  switch (action) {
    case KeyAction::Id::HIT:
      character->draw(_deck);
      Logger::get().info(current_state());
      if (is_busted(character)) {
        _state = Game::States::GAMEOVER;
        determine_winner();
      };
      break;
    case KeyAction::Id::STAND:
      next_state();
      dealers_turn();
      _state = Game::States::GAMEOVER;
      determine_winner();
      break;
    default:
      break;
  }
}

void Game::next_state() {
  // Game should be continuing..
  assert(_state != Game::States::GAMEOVER);

  int8_t NUMBER_OF_STATE = 4;
  int8_t new_state = (static_cast<int8_t>(_state) + 1) % NUMBER_OF_STATE;
  _state = new_state != 0 ? static_cast<Game::States>(new_state)
                          : Game::States::GAMEOVER;
}

bool Game::alive() {
  return _state != Game::States::GAMEOVER;
}

std::string Game::current_state() {
  return _ID + ":\nCurrent State:\nDealer:\t" +
         std::to_string(_dealer->hand_values_ints()) + "\nPlayer:\t" +
         std::to_string(_players.back()->hand_values_ints()) + "\n";
}

bool Game::is_busted(Player* player) {
  const int& total = player->hand_values_ints();

  return total > 21;
}

void Game::determine_winner() {
  const int& player_total = _players.back()->hand_values_ints();
  const int& dealer_total = _dealer->hand_values_ints();

  Logger::get().info(current_state());

  if (player_total > 21) {
    std::cout << "Player busted! Dealer wins!" << std::endl;
    _state = Game::States::GAMEOVER;
  } else if (dealer_total > 21) {
    std::cout << "Dealer busted! Player wins!" << std::endl;
    _state = Game::States::GAMEOVER;
  } else if (player_total > dealer_total) {
    std::cout << "Player wins!" << std::endl;
    _state = Game::States::GAMEOVER;
  } else if (player_total < dealer_total) {
    std::cout << "Dealer wins!" << std::endl;
    _state = Game::States::GAMEOVER;
  }
}
}  // namespace blackjack
