#include "lakos_book/namespace_issue/my_util.hpp"

// Does not compile
// void my_util::foo(int) {
//   //
// }

namespace my_util {
int bar(char) {
  return 0;
}
}
