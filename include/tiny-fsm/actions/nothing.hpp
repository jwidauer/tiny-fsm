#pragma once

#include "tiny-fsm/types/types.hpp"
#include "tiny-fsm/utils/static_string.hpp"

namespace fsm {

struct Nothing {
  template <typename Machine, typename State, typename Event>
  void execute(Machine&, State&, const Event&) {}
};

static constexpr auto stringify(Types<Nothing>) { return StaticString{"Nothing"}; }

}  // namespace fsm
