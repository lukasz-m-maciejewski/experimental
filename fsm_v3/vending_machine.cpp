#include <boost/variant.hpp>
#include <iostream>

#include "fsm_v3/fsm.hpp"

namespace vending_machine {
struct ButtonPressed {
  int choice;
};
struct CoinInserted {
  int value;
};
struct Reset {};

using Event = boost::variant<ButtonPressed, CoinInserted, Reset>;

class Idle {
 public:
  Idle() : funds_{0} { std::cout << "Idle state created\n"; }
  Idle(int funds) : funds_{funds} {
    std::cout << "Idle state created with funds:" << funds << '\n';
  }
  Idle(const Idle& other) : funds_{other.funds_} {
    std::cout << "Copying Idle state\n";
  }
  void operator=(const Idle& other) {
    std::cout << "Copy assigning Idle\n";
    funds_ = other.funds_;
  }

  Idle(Idle&& other) : funds_{other.funds_} {
    std::cout << "Moving Idle state\n";
  }
  void operator=(Idle&& other) {
    std::cout << "Move assigning Idle\n";
    funds_ = other.funds_;
  }
  ~Idle() { std::cout << "Leaving idle state\n"; }
  int funds_;
};

class VendingMachine;

struct Error {
  Error() { std::cout << "Error state created\n"; }
  Error(const Error&) { std::cout << "Error state copied\n"; }
  void operator=(const Error&) { std::cout << "Error state copy assigned\n"; }
  Error(Error&&) { std::cout << "Error state moved\n"; }
  void operator=(Error&&) { std::cout << "Error state move assigned\n"; }
  ~Error() { std::cout << "Error state destroyed\n"; }

  void OnEntry(VendingMachine& m);
};

struct FetchingItem {};

using State = boost::variant<Idle, Error, FetchingItem>;
class VendingMachine
    : public state_machine::FSMBase<VendingMachine, Event, State> {
 public:
  VendingMachine() {}

  state_machine::Transition<State> HandleEvent(Idle& state,
                                               const ButtonPressed& event) {
    std::cout << "handling ButtonPressed in Idle state\n";
    std::cout << "choice:" << event.choice << '\n';
    if (state.funds_ >= 20) {
      std::cout << "got enough funds :-)\n";
      return state_machine::MakeTransition<State>(FetchingItem{});
    } else {
      std::cout << "not enough funds :-(\n";
      return state_machine::MakeTransition<State>(Error{});
    }
  }

  state_machine::Transition<State> HandleEvent(FetchingItem&,
                                               const ButtonPressed&) {
    std::cout << "Handling Button pressed in FetchinItem";
    return state_machine::NoTransition();
  }

  state_machine::Transition<State> HandleEvent(Idle& state,
                                               const CoinInserted& event) {
    std::cout << "Handling CoinInserted in Idle\n";
    state.funds_ += event.value;
    return state_machine::NoTransition();
    // return state_machine::MakeTransition<State>(Idle{state.funds_ +
    // event.value});
  }

  template <typename S>
  state_machine::Transition<State> HandleEvent(S&, const CoinInserted& event) {
    giveChange(event.value);
    return state_machine::NoTransition();
  }

  template <typename S, typename E>
  state_machine::Transition<State> HandleEvent(S&, const E&) {
    std::cout << "unexpected event!!!\n";
    return state_machine::NoTransition();
  }

  int val = 10;

 private:
  void giveChange(int value) {
    std::cout << "returing " << value << " money\n";
  }
};

void Error::OnEntry(VendingMachine& m) {
  std::cout << m.val << "ERROR ENTRY ERROR ERROR!\n";
}
}  // namespace vending_machine

int main() {
  // auto has_OnEntry =
  //     boost::hana::is_valid([](auto&& x) -> decltype(x.OnEntry()) {});
  // auto error = vending_machine::Error();
  // static_assert(has_OnEntry(error), "");
  // auto idle = vending_machine::Idle();
  // static_assert(!has_OnEntry(idle), "");
  vending_machine::VendingMachine m;
  // m.Dispatch(vending_machine::CoinInserted{20});
  std::cout << "Phase 2\n";
  m.Dispatch(vending_machine::ButtonPressed{10});
  m.Dispatch(vending_machine::CoinInserted{25});
  m.Dispatch(vending_machine::Reset{});
}
