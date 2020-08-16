#include <iostream>

int g_stuff = 0;

int pure_fun (int x) __attribute__((pure));

int pure_fun (int x) {
  return x + g_stuff;
}

int main(int argc, [[maybe_unused]] char* argv[]) {
  std::cout << pure_fun(argc) << '\n';
  g_stuff = 10;
  std::cout << pure_fun(argc) << '\n';
  g_stuff = 20;
  std::cout << pure_fun(argc) << '\n';
}
