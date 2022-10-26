#pragma once

#include <tuple>
#include <variant>

#include "tiny-fsm/types/types.hpp"

namespace fsm {

template <typename... States>
class StateMachine {
 public:
  StateMachine() = default;

  explicit StateMachine(States... states) : states_(std::move(states)...) {}

  template <typename State>
  State& transitionTo() {
    State& state = std::get<State>(states_);
    current_state_ = &state;
    return state;
  }

  template <typename Event>
  void handle(const Event& event) {
    handleBy(event, *this);
  }

  template <typename Event, typename Machine>
  void handleBy(const Event& event, Machine& machine) {
    auto passEventToState = [&machine, &event](auto statePtr) {
      auto action = statePtr->handle(event);
      action.execute(machine, *statePtr, event);
    };
    std::visit(passEventToState, current_state_);
  }

  constexpr static Types<States...> getStateTypes() noexcept { return {}; }

  template <typename State>
  constexpr bool isInState() const noexcept {
    return std::holds_alternative<State*>(current_state_);
  }

 private:
  std::tuple<States...> states_;
  std::variant<States*...> current_state_{&std::get<0>(states_)};
};

}  // namespace fsm
