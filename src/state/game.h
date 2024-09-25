#include <memory>
#include <string>
#include <vector>
#include "../gameplay/characters/player.h"
#include "../io/key_action.h"

namespace blackjack {
class Game {

 public:
  Game(std::unique_ptr<Player> dealer, std::unique_ptr<Deck> deck);
  ~Game();
  void start();
  void add_player(std::unique_ptr<Player> player);
  void send_action(const KeyAction::Id& action);
  void handle_action(Player* character, const KeyAction::Id& action);
  void determine_winner();
  Player* current_player();
  bool alive();

 private:
  std::string _ID;

  enum States : int8_t {
    DEALER_TURN,
    PLAYER_TURN,
    GAMEOVER,
    GAMESTART,
  };

  enum PlayerState : int8_t {
    ALIVE,
    BUSTED,
    BLACKJACK,
  };

  void dealers_turn();

  std::string current_state();

  PlayerState blackjack_or_busted(const Player& player);

  std::vector<std::unique_ptr<Player>> _players;

  std::unique_ptr<Player> _dealer;

  std::unique_ptr<Deck> _deck;

  States _state;

  int _player_position = 0;
};
}  // namespace blackjack
