#include <tiny-fsm/actions/nothing.hpp>
#include <tiny-fsm/actions/transition_to.hpp>
#include <tiny-fsm/state_machine.hpp>
#include <tiny-fsm/types/types.hpp>

#include <doctest.h>

TEST_SUITE_BEGIN("[State Machine]");

using namespace fsm;

struct Latch {
  void set() noexcept { is_set = true; }

  bool read_and_reset() noexcept {
    const bool result = is_set;
    is_set = false;
    return result;
  }

 private:
  bool is_set = false;
};

struct StateA;
struct StateB;

struct EventA {};
struct EventB {};

static Latch entered_a;
static Latch exited_a;

struct StateA {
  template <typename Event>
  void onEnter(const Event&) const noexcept {
    entered_a.set();
  }

  template <typename Event>
  void onLeave(const Event&) const noexcept {
    exited_a.set();
  }

  Nothing handle(const EventA&) const noexcept { return {}; }
  TransitionTo<StateB> handle(const EventB&) const noexcept { return {}; }
};

struct StateB {
  TransitionTo<StateA> handle(const EventA&) const noexcept { return {}; }
  Nothing handle(const EventB&) const noexcept { return {}; }
};

using TestStateMachine = StateMachine<StateA, StateB>;

TEST_CASE("State Machine") {
  SUBCASE("Initial state") {
    TestStateMachine sm;
    CHECK(sm.isInState<StateA>());
  }

  SUBCASE("Getting state types works") {
    constexpr auto stateTypes = TestStateMachine::getStateTypes();
    CHECK(size(stateTypes) == 2);
    CHECK(std::is_same_v<std::remove_const_t<decltype(stateTypes)>, Types<StateA, StateB>>);
  }

  SUBCASE("Transitions work") {
    TestStateMachine sm;

    sm.handle(EventB{});
    REQUIRE(sm.isInState<StateB>());
    CHECK(exited_a.read_and_reset());

    sm.handle(EventA{});
    REQUIRE(sm.isInState<StateA>());
    CHECK(entered_a.read_and_reset());

    sm.handle(EventA{});
    CHECK(sm.isInState<StateA>());
    CHECK_FALSE(exited_a.read_and_reset());
    CHECK_FALSE(entered_a.read_and_reset());
  }
}

TEST_SUITE_END();
