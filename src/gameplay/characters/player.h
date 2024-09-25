#pragma once

#include <memory>
#include <vector>
#include "../props/deck.h"

namespace blackjack {
class Player {
 public:
  void draw(Deck* deck);
  Player();
  std::vector<std::unique_ptr<Deck::Card>> hands_;
  void fold(std::unique_ptr<Deck::Card>* card);
  void fold_all();
  int32_t hand_values_ints();
  bool contains_ace = false;
};
}  // namespace blackjack
