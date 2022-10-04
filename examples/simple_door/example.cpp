#include <tiny-fsm/actions/nothing.hpp>
#include <tiny-fsm/actions/transition_to.hpp>
#include <tiny-fsm/state_machine.hpp>

#include <functional>
#include <iostream>

using namespace fsm;

struct OpenEvent {};

struct CloseEvent {};

struct ClosedState;
struct OpenState;

struct ClosedState {
  TransitionTo<OpenState> handle(const OpenEvent&) const {
    std::cout << "Opening the door..." << std::endl;
    return {};
  }

  Nothing handle(const CloseEvent&) const {
    std::cout << "Cannot close. The door is already closed!" << std::endl;
    return {};
  }
};

struct OpenState {
  Nothing handle(const OpenEvent&) const {
    std::cout << "Cannot open. The door is already open!" << std::endl;
    return {};
  }

  TransitionTo<ClosedState> handle(const CloseEvent&) const {
    std::cout << "Closing the door..." << std::endl;
    return {};
  }
};

using Door = StateMachine<ClosedState, OpenState>;

int main() {
  Door door;

  door.handle(OpenEvent{});
  door.handle(CloseEvent{});

  door.handle(CloseEvent{});
  door.handle(OpenEvent{});

  return 0;
}
