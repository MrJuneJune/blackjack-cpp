#pragma once

#include <memory>
#include <vector>
#include "../props/deck.h"

namespace blackjack {
class Player {
 public:
  Player();
  ~Player();
  // Probably need to use shared ptr for this.
  void draw(Deck* deck);

  std::vector<std::unique_ptr<Deck::Card>> hands_;
  void fold(std::unique_ptr<Deck::Card>* card);
  void fold_all();
  int32_t hand_values_ints() const;
  bool contains_ace = false;
};
}  // namespace blackjack
