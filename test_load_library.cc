#include <iostream>
#include "lazy/lazy_utils.h"

void test_lazy_utils();

int main() {
  test_lazy_utils();
}

void test_lazy_utils() {
 #define TEST_CODE(Ty) \
  { \
  Ty lhs = 123, rhs = 321; \
  auto res = lazy::_add_##Ty(lhs, rhs); \
  auto target = lhs + rhs; \
  auto diff = res - target; \
  std::cout << "\n" << __func__ << ": diff=" << diff << "\n"; \
  }

  TEST_CODE(int);
  TEST_CODE(float);
  TEST_CODE(double);

#undef TEST_CODE
 
}
