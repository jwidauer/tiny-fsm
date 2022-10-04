#pragma once

#include "tiny-fsm/types/types.hpp"

namespace fsm {

template <typename Operation>
class MapAndJoin {
 public:
  constexpr MapAndJoin(Operation operation) : operation_{std::move(operation)} {}

  template <typename... Ts>
  constexpr auto operator()(Types<Ts>... rhs) {
    return (operation_(rhs) + ...);
  }

 private:
  Operation operation_;
};

}  // namespace fsm
