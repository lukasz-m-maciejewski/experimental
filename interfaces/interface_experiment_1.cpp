#include <iostream>

class Interface {
public:
  virtual void foo() = 0;
};

class Impl : public Interface {
private:
  void foo() override {
    std::cout << "hello\n";
  }
};

int main() {
  Impl impl;
  // impl.foo();

  Interface* iface = &impl;
  iface->foo();
}
