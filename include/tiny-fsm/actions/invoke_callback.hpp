/****************************************************************************
 *
 *      Copyright (c) 2022, Auterion Ltd. All rights reserved.
 *
 * All information contained herein is, and remains the property of
 * Auterion Ltd. and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Auterion Ltd. and its
 * suppliers and may be covered by U.S. and Foreign Patents, patents in
 * process, and are protected by trade secret or copyright law.
 * Reproduction or distribution, in whole or in part, of this information
 * or reproduction of this material is strictly forbidden unless prior
 * written permission is obtained from Auterion Ltd.
 *
 ****************************************************************************/

/**
 * @file invoke_callback.h
 *
 * @author Jakob Widauer (jakob@auterion.com)
 */

#pragma once

#include <functional>

#include "tiny-fsm/types/types.hpp"
#include "tiny-fsm/utils/static_string.hpp"

namespace fsm {

template <typename... Args>
struct InvokeCallback {
  InvokeCallback(std::function<void(Args&...)> callback, Args&... args)
      : _callback(callback), _args(args...) {}

  template <typename Machine, typename State, typename Event>
  void execute(Machine&, State&, const Event&) {
    std::apply(_callback, _args);
  }

 private:
  std::function<void(Args&...)> _callback;
  std::tuple<Args...> _args;
};

template <typename... Args>
static constexpr auto stringify(Types<InvokeCallback<Args...>>) {
  return StaticString{"InvokeCallback<"} + stringify(Types<Args>{}...) + StaticString{">"};
}

}  // namespace fsm
