#pragma once

#include <boost/variant.hpp>
#include <utility>

namespace state_machine {
template <typename FSM, typename State>
class EventDispatcher {
 public:
  EventDispatcher(FSM& fsm) : fsm_{fsm} {}
  template <typename ActiveState, typename Event>
  State operator()(ActiveState&& state, const Event& event) {
    return fsm_.HandleEvent(std::move(state), event);
  }

 private:
  FSM& fsm_;
};

template <typename FSM, typename Event, typename State>
class FSMBase {
 public:
  void Dispatch(const Event& event) {
    EventDispatcher<FSM, State> dispatcher(static_cast<FSM&>(*this));
    this->fsmState_ = std::move(
        boost::apply_visitor(dispatcher, std::move(fsmState_), event));
  }

 protected:
  State fsmState_;
};
}  // namespace state_machine
