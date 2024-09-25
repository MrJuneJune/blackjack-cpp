#include <string>
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
  bool alive();

 private:
  std::string _ID;

  enum States : int8_t {
    DEALER_TURN,
    PLAYER_TURN,
    GAMEOVER,
    GAMESTART,
  };

  void next_state();

  void dealers_turn();

  std::string current_state();

  bool is_busted(Player* player);

  std::vector<Player*> _players;

  Player* _dealer;

  Deck* _deck;

  States _state;
};
}  // namespace blackjack
