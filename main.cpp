#include <iostream>
#include "src/gameplay/characters/player.h"
#include "src/gameplay/props/deck.h"
#include "src/state/game.h"
#include "src/utils/loggers.h"

int main() {
  blackjack::Player player;
  blackjack::Player dealer;
  blackjack::Deck deck;
  blackjack::Logger::get().init("logfile.txt");

  blackjack::Game game(&player, &dealer, &deck);

  while (game.alive()) {
    int input = 0;
    std::cout << "Enter 1 to HIT, 2 to STAND: \n";
    std::cin >> input;

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
