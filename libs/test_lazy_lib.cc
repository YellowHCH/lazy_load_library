#include "lazy_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void test_lazy_add();
void test_lazy_div();

int main() {
  printf("Test lazy utils\n");

  test_lazy_add();
  test_lazy_div();

  printf("Test lazy utils done\n");
}


void test_lazy_add() {
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

void test_lazy_div() {
#define TEST_CODE(Ty) \
  { \
  Ty lhs = 123, rhs = 321; \
  auto res = lazy::_div_##Ty(lhs, rhs); \
  auto target = lhs / rhs; \
  auto diff = res - target; \
  std::cout << "\n" << __func__ << ": diff=" << diff << "\n"; \
  }

  TEST_CODE(int);
  TEST_CODE(float);
  TEST_CODE(double);

#undef TEST_CODE
}
