#include <iostream>

template <typename... Ts>
void my_print(Ts... ts, std::ostream& t)  {
  (t << ... << ts) << '\n';
}

int main() {
  my_print("abc", 1, 2, 3, std::cout );
}
