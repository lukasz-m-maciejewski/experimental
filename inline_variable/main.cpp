#include <iostream>

namespace my {
extern int const x;
}
int main() { std::cout << my::x << '\n'; }
