#include <tiny-fsm/actions/by_default.hpp>
#include <tiny-fsm/actions/maybe.hpp>
#include <tiny-fsm/actions/nothing.hpp>
#include <tiny-fsm/actions/on.hpp>
#include <tiny-fsm/actions/transition_to.hpp>
#include <tiny-fsm/actions/will.hpp>
#include <tiny-fsm/state_machine.hpp>

#include <cstdint>

using namespace fsm;

struct OpenEvent {};

struct CloseEvent {};

struct LockEvent {
  uint32_t newKey;
};

struct UnlockEvent {
  uint32_t key;
};

struct ClosedState;
struct OpenState;
class LockedState;

struct ClosedState : public Will<ByDefault<Nothing>, On<LockEvent, TransitionTo<LockedState>>,
                                 On<OpenEvent, TransitionTo<OpenState>>> {};

struct OpenState : public Will<ByDefault<Nothing>, On<CloseEvent, TransitionTo<ClosedState>>> {};

class LockedState : public ByDefault<Nothing> {
 public:
  using ByDefault::handle;

  LockedState(uint32_t key) : key(key) {}

  void onEnter(const LockEvent& e) { key = e.newKey; }

  Maybe<TransitionTo<ClosedState>> handle(const UnlockEvent& e) {
    if (e.key == key) {
      return TransitionTo<ClosedState>{};
    }
    return Nothing{};
  }

 private:
  uint32_t key;
};

using Door = StateMachine<ClosedState, OpenState, LockedState>;
