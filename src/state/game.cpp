#include "./game.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include "../gameplay/characters/player.h"
#include "io/key_action.h"

namespace blackjack {
Game::Game(Player* player1, Player* dealer, Deck* deck) {
  _players.push_back(player1);
  _dealer = dealer;
  _deck = deck;
  _state = Game::States::GAMESTART;

  // Unneccessary, but just for testing
  _players.back()->draw(_deck);
  _state = Game::States::PLAYER_TURN;
}

void Game::send_action(const KeyAction::Id& action) {
  switch (_state) {
    case Game::States::DEALER_TURN:
      handle_action(_dealer, action);
      break;
    case Game::States::PLAYER_TURN:
      // TODO(June): Update this to include a logic for which player it is for ?
      handle_action(_players.back(), action);
      break;
    default:
      break;
  }
}

void Game::handle_action(Player* character, const KeyAction::Id& action) {
  switch (action) {
    case KeyAction::Id::HIT:
      character->draw(_deck);
      determine_winner();
      break;
    case KeyAction::Id::STAND:
      next_state();
      break;
    default:
      break;
  }
}

void Game::next_state() {
  int8_t new_state = (static_cast<int8_t>(_state) + 1) % 4;
  _state = new_state != 0 ? static_cast<Game::States>(new_state)
                          : Game::States::GAMEOVER;
}

void Game::determine_winner() {
  const int& player_total = _players.back()->hand_values_ints();
  const int& dealer_total = _dealer->hand_values_ints();

  std::cout << "Player Total: " << player_total << std::endl;
  std::cout << "Dealer Total: " << dealer_total << std::endl;

  if (player_total > 21) {
    std::cout << "Player busted! Dealer wins!" << std::endl;
  } else if (dealer_total > 21) {
    std::cout << "Dealer busted! Player wins!" << std::endl;
  } else if (player_total > dealer_total) {
    std::cout << "Player wins!" << std::endl;
  } else if (player_total < dealer_total) {
    std::cout << "Dealer wins!" << std::endl;
  } else {
    std::cout << "Current State is " << _state;
  }
}
}  // namespace blackjack
