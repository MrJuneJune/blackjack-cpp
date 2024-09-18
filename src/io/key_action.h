#pragma once

#include <cstdint>

namespace blackjack {
namespace KeyAction {
enum Id : int32_t { HIT, STAND };

inline Id actionbyid(int32_t id) {
  return static_cast<Id>(id);
}
}  // namespace KeyAction
}  // namespace blackjack
