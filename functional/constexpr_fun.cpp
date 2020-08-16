#include <fmt/core.h>

extern int g_x;

struct S {
  int x;
  int y;
};

constexpr int triple(int x) {
  if (x >= 0)
    return 3 * x;
  else
    return 2 * x;
}

constexpr void fill(int* px) {
  *px = 7;
}

constexpr int addS(S s) {
  return s.x + s.y;
}

int main(int argc, [[maybe_unused]] char* argv[]) {
  int xx = 10;
  fill(&xx);
  fmt::print("Hello {}, {}, {}\n", argc, triple(argc), triple(-7));
  fmt::print("Howdy {}\n", xx);
  fmt::print("S: {}\n", addS({1, 3}));
}
