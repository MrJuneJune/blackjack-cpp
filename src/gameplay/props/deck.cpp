#include "./deck.h"
#include <algorithm>
#include <memory>
#include <random>
#include "../utils/loggers.h"

namespace blackjack {
Deck::Deck() {
  create_deck();
  shuffle();
}

void Deck::create_deck() {
  for (int i = Deck::Numbers::ACES; i <= Deck::Numbers::KING; i++) {
    for (int j = Deck::Suits::HEARTS; j <= Deck::Suits::SPADES; j++) {
      std::unique_ptr<Deck::Card> new_card = std::make_unique<Deck::Card>();
      new_card->number = Deck::Numbers(i);
      new_card->suit = Deck::Suits(j);

      cards_.push_back(std::move(new_card));
    }
  }
}

std::unique_ptr<Deck::Card> Deck::draw() {
  if (cards_.empty()) {
    return nullptr;
  }
  std::unique_ptr<Deck::Card> card = std::move(cards_.back());
  cards_.pop_back();
  return card;
}

void Deck::reset() {
  for (auto& card : cards_) {
    delete card.release();
  }
  cards_.clear();
  create_deck();
  shuffle();
}

void Deck::shuffle() {
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(cards_.begin(), cards_.end(), g);
}

Deck::~Deck() {
  Logger::get().info("DELETING DECK");
}
}  // namespace blackjack
