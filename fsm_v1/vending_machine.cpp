#include <boost/variant.hpp>
#include <iostream>

#include "fsm_v1/fsm.hpp"

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
  Idle() { std::cout << "Idle state created\n"; }
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

struct Error {
  Error() { std::cout << "Error state created\n"; }
  Error(const Error&) { std::cout << "Error state copied\n"; }
  void operator=(const Error&) { std::cout << "Error state copy assigned\n"; }
  Error(Error&&) { std::cout << "Error state moved\n"; }
  void operator=(Error&&) { std::cout << "Error state move assigned\n"; }
  ~Error() { std::cout << "Error state destroyed\n"; }
};

struct FetchingItem {};

using State = boost::variant<Idle, Error, FetchingItem>;
class VendingMachine
    : public state_machine::FSMBase<VendingMachine, Event, State> {
 public:
  VendingMachine() {}

  State HandleEvent(Idle&& state, const ButtonPressed& event) {
    std::cout << "handling ButtonPressed in Idle state\n";
    std::cout << "choice:" << event.choice << '\n';
    if (state.funds_ > 20) {
      std::cout << "got enough funds :-)\n";
      return FetchingItem{};
    } else {
      std::cout << "not enough funds :-(\n";
      return Error{};
    }
  }

  State HandleEvent(FetchingItem&& state, const ButtonPressed&) {
    return std::move(state);
  }

  State HandleEvent(Idle&& state, const CoinInserted& event) {
    std::cout << "Handling CoinInserted in Idle\n";
    return Idle{state.funds_ + event.value};
  }

  template <typename S>
  State HandleEvent(S&& state, const CoinInserted& event) {
    giveChange(event.value);
    return std::move(state);
  }

  template <typename S, typename E>
  State HandleEvent(S&& state, const E&) {
    std::cout << "unexpected event!!!\n";
    return state;
  }

 private:
  void giveChange(int value) {
    std::cout << "returing " << value << " money\n";
  }
};
}  // namespace vending_machine

int main() {
  vending_machine::VendingMachine m;
  m.Dispatch(vending_machine::CoinInserted{20});
  m.Dispatch(vending_machine::ButtonPressed{10});
  m.Dispatch(vending_machine::Reset{});
}
