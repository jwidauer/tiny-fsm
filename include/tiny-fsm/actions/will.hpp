#pragma once

namespace fsm {

template <typename... Handlers>
struct Will : Handlers... {
  using Handlers::handle...;
};

}  // namespace fsm
