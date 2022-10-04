#pragma once

#include <utility>
#include <variant>

namespace fsm {

template <typename... Actions>
class OneOf {
 public:
  template <typename T>
  OneOf(T&& arg) : options_{std::forward<T>(arg)} {}

  template <typename Machine, typename State, typename Event>
  void execute(Machine& machine, State& state, const Event& event) {
    std::visit([&machine, &state, &event](auto& action) { action.execute(machine, state, event); },
               options_);
  }

 private:
  std::variant<Actions...> options_;
};

template <typename... Actions>
constexpr auto stringify(Types<OneOf<Actions...>>) {
  return StaticString{"OneOf<"} + stringify(Types<Actions>{}...) + StaticString{">"};
}

}  // namespace fsm
