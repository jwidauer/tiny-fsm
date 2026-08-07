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

#include <utility>
#include <variant>

#include "tiny-fsm/types/types.hpp"
#include "tiny-fsm/utils/static_string.hpp"

namespace fsm {

template <typename... Actions>
class OneOf {
 public:
  template <typename T>
  constexpr explicit OneOf(T&& arg) : options(std::forward<T>(arg)) {}

  template <typename Machine, typename State, typename Event>
  void execute(Machine& machine, State& state, const Event& event) {
    std::visit([&machine, &state, &event](auto& action) { action.execute(machine, state, event); },
               options);
  }

 private:
  std::variant<Actions...> options;
};

template <typename... Actions>
constexpr auto stringify(Types<OneOf<Actions...>>) {
  return StaticString{"OneOf<"} + stringify(Types<Actions>{}...) + StaticString{">"};
}

}  // namespace fsm
