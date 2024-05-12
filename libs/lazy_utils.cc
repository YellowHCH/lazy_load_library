#include "lazy_utils.h"

namespace lazy {
#define def_add(Ty) \
  Ty _add_##Ty(Ty &lhs, Ty &rhs) { return lhs + rhs; }

#define def_div(Ty) \
  Ty _div_##Ty(Ty &lhs, Ty &rhs) { return lhs / rhs; }

def_add(int);
def_add(float);
def_add(double);
def_div(int);
def_div(float);
def_div(double);

#undef def_add
#undef def_div

}; // namespace lazy
