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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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

#include <cstddef>

namespace fsm {

template <typename... Ts>
struct Types {};

template <typename... Lhs, typename... Rhs>
constexpr auto operator+(Types<Lhs...>, Types<Rhs...>) {
  return Types<Lhs..., Rhs...>{};
}

template <typename Lhs, typename... Rhs>
constexpr auto operator*(Types<Lhs>, Types<Rhs...>) {
  return Types<Types<Lhs, Rhs>...>{};
}

template <typename... Lhs, typename Rhs>
constexpr auto operator*(Types<Lhs...>, Rhs rhs) {
  return ((Types<Lhs>{} * rhs) + ...);
}

template <typename... Ts, typename Operation>
constexpr auto operator|(Types<Ts...>, Operation oper) {
  return oper(Types<Ts>{}...);
}

template <typename... Ts>
constexpr std::size_t size(Types<Ts...>) {
  return sizeof...(Ts);
}

}  // namespace fsm
