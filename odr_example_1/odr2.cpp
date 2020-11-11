#include <stdio.h>

#include "odr.hpp"

class CDummy : public CBase {
 public:
  void xxx() override { printf("odr TWO dummy: World\n"); }
};

CBase* odr2_create() { return new CDummy(); }
