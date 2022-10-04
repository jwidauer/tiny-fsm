#pragma once

#include "tiny-fsm/actions/nothing.hpp"
#include "tiny-fsm/actions/one_of.hpp"

namespace fsm {

template <typename Action>
struct Maybe : public OneOf<Action, Nothing> {
  using OneOf<Action, Nothing>::OneOf;
};

template <typename Action>
static constexpr auto stringify(Types<Maybe<Action>>) {
  return StaticString{"Maybe<"} + stringify(Types<Action>{}) + StaticString{">"};
}

}  // namespace fsm
