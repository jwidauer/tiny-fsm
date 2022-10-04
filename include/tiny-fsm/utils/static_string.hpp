#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#include "tiny-fsm/utils/array_utils.hpp"

namespace fsm {

template <std::size_t N>
class StaticString {
 public:
  constexpr StaticString(const char (&chars)[N]) : chars_{toStdArray(chars)} {}

  constexpr StaticString(const std::array<const char, N>& chars) : chars_{chars} {}

  template <std::size_t M>
  constexpr StaticString<N + M - 1> operator+(const StaticString<M>& rhs) const {
    return join(resize<N - 1>(chars_, '\0'), rhs.chars_);
  }

  constexpr bool operator==(const StaticString<N>& rhs) const {
    return areEqual(chars_, rhs.chars_);
  }

  constexpr std::size_t length() const { return N - 1; }

  template <std::size_t TargetLen>
  constexpr StaticString<TargetLen + 1> changeLength(char fill) const {
    constexpr std::array<const char, 1> stringEnd{'\0'};
    return join(resize<TargetLen>(resize<N - 1>(chars_, fill), fill), stringEnd);
  }

  template <std::size_t M>
  friend class StaticString;

  constexpr const char* data() const { return chars_.data(); }

 private:
  std::array<const char, N> chars_;
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
