#include "./player.h"
#include <cstdint>
#include <vector>

namespace blackjack {
Player::Player() {
  std::vector<std::unique_ptr<Deck::Card>> hands_ = {};
}

void Player::draw(Deck* deck) {
  hands_.push_back(deck->draw());
}

void Player::fold(std::unique_ptr<Deck::Card>* card) {
  delete card->release();
}

void Player::fold_all() {
  for (auto& card : hands_) {
    Player::fold(&card);
  }
  hands_.clear();
}

int32_t Player::hand_values_ints() {
  int32_t sums = 0;
  for (auto& card : hands_) {
    sums += card->number;
  }
  return sums;
}
}  // namespace blackjack
