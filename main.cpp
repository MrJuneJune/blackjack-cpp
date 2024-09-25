#include <iostream>
#include <memory>
#include "src/gameplay/characters/player.h"
#include "src/gameplay/props/deck.h"
#include "src/state/game.h"
#include "src/utils/loggers.h"

int main() {
  blackjack::Logger::get().init("logfile.txt");

  std::unique_ptr<blackjack::Player> dealer =
      std::make_unique<blackjack::Player>();

  std::unique_ptr<blackjack::Deck> deck = std::make_unique<blackjack::Deck>();

  blackjack::Game game(std::move(dealer), std::move(deck));

  // How many numbers of player we want to play wtih
  int number_of_players = 0;
  std::cout << "Enter number of players: \n";
  std::cin >> number_of_players;
  std::cout << "\n---------\n\n";
  while (number_of_players) {
    std::unique_ptr<blackjack::Player> player =
        std::make_unique<blackjack::Player>();
    game.add_player(std::move(player));
    number_of_players -= 1;
  }

  // start the game
  game.start();

  while (game.alive()) {
    int input = 0;
    std::cout << "Enter 1 to HIT, 2 to STAND: \n";
    std::cin >> input;
    std::cout << "\n---------\n\n";

    if (input == 1) {
      game.send_action(blackjack::KeyAction::HIT);
    } else if (input == 2) {
      game.send_action(blackjack::KeyAction::STAND);
    } else {
      std::cout << "Invalid input, please enter 1 or 2.\n";
    }

    if (!game.alive()) {
      std::cout << "Game over!\n";
      break;
    }
  }

  return 0;
}
