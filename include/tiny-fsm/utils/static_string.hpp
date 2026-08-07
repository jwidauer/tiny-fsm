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

#include "tiny-fsm/utils/array_utils.hpp"

namespace fsm {

template <std::size_t N>
class StaticString {
 public:
  constexpr explicit StaticString(const char (&chars)[N]) : chars(toStdArray(chars)) {}

  constexpr explicit StaticString(const std::array<const char, N>& chars) : chars(chars) {}

  template <std::size_t M>
  constexpr StaticString<N + M - 1> operator+(const StaticString<M>& rhs) const {
    return StaticString<N + M - 1>{join(resize<N - 1>(chars, '\0'), rhs.chars)};
  }

  constexpr bool operator==(const StaticString<N>& rhs) const { return areEqual(chars, rhs.chars); }

  constexpr std::size_t length() const { return N - 1; }

  template <std::size_t TargetLen>
  constexpr StaticString<TargetLen + 1> changeLength(char fill) const {
    constexpr std::array<const char, 1> stringEnd{'\0'};
    return StaticString<TargetLen + 1>{
        join(resize<TargetLen>(resize<N - 1>(chars, fill), fill), stringEnd)};
  }

  template <std::size_t M>
  friend class StaticString;

  constexpr const char* data() const { return chars.data(); }

 private:
  std::array<const char, N> chars;
};

namespace tests {
namespace {

[[maybe_unused]] constexpr void testAdding() {
  constexpr StaticString lhs{"abc"};
  constexpr StaticString rhs{"de"};
  constexpr StaticString expected{"abcde"};
  static_assert(expected == lhs + rhs);
}

[[maybe_unused]] constexpr void testLength() {
  constexpr StaticString lhs{"abc"};
  constexpr std::size_t expected{3};
  static_assert(lhs.length() == expected);
}

[[maybe_unused]] constexpr void test0Length() {
  constexpr StaticString lhs{""};
  constexpr std::size_t expected{0};
  static_assert(lhs.length() == expected);
}

[[maybe_unused]] constexpr void testChangeLength() {
  constexpr StaticString shorter{"abc"};
  constexpr StaticString longer{"abcdef"};
  constexpr StaticString empty{""};

  constexpr std::size_t minLength{5};
  constexpr StaticString expectedShorter{"abcxx"};
  constexpr StaticString expectedLonger{"abcde"};
  constexpr StaticString expectedEmpty{"zzzzz"};

  constexpr auto res = shorter.changeLength<minLength>('x');

  static_assert(res.data()[3] == expectedShorter.data()[3]);

  static_assert(shorter.changeLength<minLength>('x') == expectedShorter);
  static_assert(longer.changeLength<minLength>('y') == expectedLonger);
  static_assert(empty.changeLength<minLength>('z') == expectedEmpty);
}

}  // namespace
}  // namespace tests

}  // namespace fsm
