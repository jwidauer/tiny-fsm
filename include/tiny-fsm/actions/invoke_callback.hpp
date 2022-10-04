#pragma once

#include <functional>

#include "tiny-fsm/types/types.hpp"
#include "tiny-fsm/utils/static_string.hpp"

namespace fsm {

template <typename... Args>
struct InvokeCallback {
  InvokeCallback(std::function<void(Args&...)> callback, Args... args)
      : callback_{std::move(callback)}, args_{std::move(args)...} {}

  template <typename Machine, typename State, typename Event>
  void execute(Machine&, State&, const Event&) {
    std::apply(callback_, args_);
  }

 private:
  std::function<void(Args&...)> callback_;
  std::tuple<Args...> args_;
};

template <typename... Args>
static constexpr auto stringify(Types<InvokeCallback<Args...>>) {
  return StaticString{"InvokeCallback<"} + stringify(Types<Args>{}...) + StaticString{">"};
}

}  // namespace fsm
