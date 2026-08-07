/********************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2020 Michał Adamczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************/

#pragma once

#include <tuple>
#include <variant>

#include "tiny-fsm/types/types.hpp"

namespace fsm {

template <typename... States>
class StateMachine {
 public:
  constexpr StateMachine() = default;

  constexpr explicit StateMachine(States... states) : states_(std::move(states)...) {}

  template <typename State>
  auto transitionTo() -> State& {
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

  template <typename State>
  [[nodiscard]] constexpr auto isInState() const -> bool {
    return std::holds_alternative<State*>(current_state_);
  }

  constexpr static Types<States...> getStateTypes() { return {}; }

 private:
  std::tuple<States...> states_;
  std::variant<States*...> current_state_{&std::get<0>(states_)};
};

}  // namespace fsm
