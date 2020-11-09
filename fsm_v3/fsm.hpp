#pragma once

#include <boost/hana.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <typeinfo>
#include <utility>

namespace state_machine {
template <typename State>
using Transition = boost::optional<State>;

auto NoTransition() { return boost::none; }

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
      HandleEntry(static_cast<FSM&>(*this), fsmState_, *transition);
      fsmState_ = std::move(transition).value();
    }
  }

 protected:
  State fsmState_;

 private:
  void HandleEntry(FSM& self, const State& currentState, State& newState) {
    if (currentState.which() != newState.which()) {
      boost::apply_visitor(
          [&self](auto& state) { MaybeCallOnEntry(state, self); }, newState);
    }
  }

  template <typename T>
  static void MaybeCallOnEntry(T& state, FSM& fsm) {
    auto has_OnEntry = boost::hana::is_valid(
        [](auto&& s, auto&& m) -> decltype(s.OnEntry(m)) {});
    boost::hana::if_(has_OnEntry(state, fsm),
                     [](auto&& withOnEntry, FSM& m) { withOnEntry.OnEntry(m); },
                     [](auto&&, FSM&) {})(state, fsm);
  }
};
}
