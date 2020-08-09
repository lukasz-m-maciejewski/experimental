#pragma once

#include <utility>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

namespace state_machine {
template <typename State>
using Transition = boost::optional<State>;

auto NoTransition() {
  return boost::none;
}

template <typename State, typename Target>
Transition<State> MakeTransition(Target&& t) {
  return State{std::forward<Target>(t)};
}

template <typename FSM, typename State>
class EventDispatcher {
 public:
  EventDispatcher(FSM& fsm) : fsm_{fsm} {}
  template <typename ActiveState, typename Event>
  Transition<State> operator()(ActiveState& state, const Event& event) {
    return fsm_.HandleEvent(state, event);
  }

 private:
  FSM& fsm_;
};

template <typename FSM, typename Event, typename State>
class FSMBase {
 public:
  void Dispatch(const Event& event) {
    EventDispatcher<FSM, State> dispatcher(static_cast<FSM&>(*this));
    auto transition = boost::apply_visitor(dispatcher, fsmState_, event);
    if (transition) {
      fsmState_ = std::move(transition).value();
    }
  }

 protected:
  State fsmState_;
};
}
