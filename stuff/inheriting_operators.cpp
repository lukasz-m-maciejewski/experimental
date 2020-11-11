#include <iostream>


template <typename... Bs>
struct call_wrapper : public Bs... {
  call_wrapper(const Bs& ...b) : Bs{b}... {}

  using Bs::operator()...;
};


template <typename... Bs>
auto make_call_wrapper(Bs... b) {
  return call_wrapper<Bs...>{b...};
}

struct StrongInt {
  int val;
};

int main() {
  auto foo = make_call_wrapper([](int x) { return x + 1; },
                               [](StrongInt x) { return x.val + 7; } );

  std::cout << foo(10) << ' ' << foo(StrongInt{123}) << '\n';
}
