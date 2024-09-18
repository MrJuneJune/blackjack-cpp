#include <cstdint>
#include <iostream>
#include <string>
#include "gameplay/characters/player.h"
#include "gameplay/props/deck.h"
#include "io/key_action.h"
#include "state/game.h"

int main() {
  blackjack::Player player;
  blackjack::Player dealer;
  blackjack::Deck deck;

  blackjack::Game game(&player, &dealer, &deck);

  game.send_action(blackjack::KeyAction::HIT);
  game.send_action(blackjack::KeyAction::STAND);

  return 0;
}
