#include "odr.hpp"

int main(int argc, char** argv) {
  CBase* o1 = odr1_create();
  CBase* o2 = odr2_create();
  o1->xxx();
  o2->xxx();
}
