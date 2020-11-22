#include <iostream>

namespace my {
extern int const x;
inline constexpr int y = 6;
}


int first_get_x();
int second_get_x();
void const* first_get_y();
void const* second_get_y();

int main() {
  // std::cout << my::x << '\n';
  std::cout << first_get_x() << '\n';
  std::cout << second_get_x() << '\n';
  std::cout << static_cast<void const*>(&my::y) << '\n';
  std::cout << first_get_y() << '\n';
  std::cout << second_get_y() << '\n';
}
