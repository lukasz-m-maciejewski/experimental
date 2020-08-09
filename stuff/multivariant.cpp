#include <boost/variant.hpp>
#include <iostream>

struct A {};
struct B {};
struct C {};

using Letters = boost::variant<A, B, C>;

struct One {};
struct Two {};
struct Three {};

using Numbers = boost::variant<One, Two, Three>;

struct Visitor : public boost::static_visitor<bool> {
  template <typename Letter, typename Number>
  bool operator()(const Letter&, const Number&) const {
    std::cout << "unspecified types\n";
    return false;
  }
  bool operator()(const A&, const Two&) const {
    std::cout << "A2\n";
    return true;
  }
};

int main() {
  std::cout << "Hello Bazel!\n";
  Letters l1 = A{};
  Letters l2 = B{};

  Numbers n1 = One{};
  Numbers n2 = Two{};

  boost::apply_visitor(Visitor{}, l1, n1);
  boost::apply_visitor(Visitor{}, l1, n2);
}
