#include "odr.hpp"

#include <stdio.h>

class CDummy : public CBase {
 public:
  void xxx() override { printf("odr ONE dummy: Hello\n"); }
};

CBase* odr1_create() { return new CDummy(); }
