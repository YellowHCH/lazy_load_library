#pragma once

namespace lazy {
#define decl_add(Ty) \
  extern "C" Ty _add_##Ty(Ty &lhs, Ty &rhs);

#define decl_div(Ty) \
  extern "C" Ty _div_##Ty(Ty &lhs, Ty &rhs);

decl_add(int);
decl_add(float);
decl_add(double);
decl_div(int);
decl_div(float);
decl_div(double);

#undef decl_add
#undef decl_div
}; // namespace lazy
