#include <iostream>

enum class EEE {
  AAA,
  BBB,
};


int main(int argc, char* argv[]) {
  std::cout << "Hello world!\n";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << '\n';
  }
}
