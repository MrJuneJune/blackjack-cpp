#include <memory>
#include <vector>
#include "../gameplay/characters/player.h"
#include "../io/key_action.h"

namespace blackjack {
class Game {

 public:
  Game(Player* player1, Player* dealer, Deck* deck);
  void send_action(const KeyAction::Id& action);
  void handle_action(Player* character, const KeyAction::Id& action);
  void determine_winner();

 private:
  enum States : int8_t {
    DEALER_TURN,
    PLAYER_TURN,
    GAMEOVER,
    GAMESTART,
  };

  void next_state();

  std::vector<Player*> _players;

  Player* _dealer;

  Deck* _deck;

  States _state;
};
}  // namespace blackjack
