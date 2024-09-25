#pragma once

#include <memory>
#include <vector>

namespace blackjack {
class Deck {
 public:
  enum Suits {
    HEARTS,
    CLOVERS,
    DIAMONDS,
    SPADES,
  };

  enum Numbers {
    ACES = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
  };

  struct Card {
    Numbers number;
    Suits suit;
  };

  Deck();
  ~Deck();

  std::unique_ptr<Card> draw();
  void shuffle();
  void reset();
  void create_deck();

 private:
  std::vector<std::unique_ptr<Card>> cards_;
};
}  // namespace blackjack
