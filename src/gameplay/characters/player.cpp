#include "./player.h"
#include <cstdint>
#include <utility>
#include <vector>

namespace blackjack {
Player::Player() {
  std::vector<std::unique_ptr<Deck::Card>> hands_ = {};
}

void Player::draw(Deck* deck) {
  std::unique_ptr<Deck::Card> card = deck->draw();
  if (card->number == Deck::Numbers::ACES) {
    contains_ace = true;
  }
  hands_.push_back(std::move(card));
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
  int8_t number_of_aces = 0;
  for (auto& card : hands_) {
    sums += card->number;
    // If card is an ace and number is smaller than 10...
    if (sums <= 10 && card->number == 1) {
      sums += 10;
      number_of_aces += 1;
    }

    // If number is bigger than 21 and we counted aces to be 10 then, we count it as 1 instead.
    while (sums > 21 && number_of_aces > 0) {
      sums -= 10;
      number_of_aces -= 1;
    }
  }
  return sums;
}
}  // namespace blackjack
