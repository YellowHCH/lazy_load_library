#include <dlfcn.h>
#include <iostream>
#include <mutex>
#include <typeinfo>

#define CHECK(expr)                                                            \
  expr;                                                                        \
  {                                                                            \
    const char *dlsym_error = dlerror();                                       \
    if (dlsym_error) {                                                         \
      std::cerr << "dlerr: " << dlsym_error << "\n";                           \
      exit(1);                                                                 \
    }                                                                          \
  }

// forward decl
void load_library();

#define decl_add_fn(Ty) static Ty _add_##Ty(Ty &lhs, Ty &rhs);

decl_add_fn(int);
decl_add_fn(float);
decl_add_fn(double);
#undef decl_add_fn

#define decl_add_once(Ty)                                                      \
  static Ty _add_##Ty##_once(Ty &lhs, Ty &rhs) {                               \
    std::cout << "call " << __func__ << "\n";                                  \
    load_library();                                                            \
    return _add_##Ty(lhs, rhs);                                                \
  }

decl_add_once(int);
decl_add_once(float);
decl_add_once(double);

#undef decl_add_once

#define FUNC_NUMS 3

// clang-format off
static const char *const g_func_name[FUNC_NUMS] = {
  "_add_int",
  "_add_float",
  "_add_double"
};
// clang-format on

static void *g_func_tb[FUNC_NUMS] = {
    (void *)(&_add_int_once),
    (void *)(&_add_float_once),
    (void *)(&_add_double_once),
};

#define def_add_fn(Ty)                                                         \
  static Ty _add_##Ty(Ty &lhs, Ty &rhs) {                                      \
    typedef Ty (*fptr_t)(Ty &, Ty &);                                          \
    fptr_t func = (fptr_t)(g_func_tb[0]);                                      \
    return func(lhs, rhs);                                                     \
  }

def_add_fn(int);
def_add_fn(float);
def_add_fn(double);
#undef def_add_fn

static const char *get_lib_path() {
  return "/home/juger/workspace/lazy_load_library/libs/lib/liblazy_lib.so";
}

static void init() {
  std::cout << "Try to load dl from " << get_lib_path() << "\n";
  CHECK(void *handle = dlopen(get_lib_path(), RTLD_LAZY););

  if (!handle) {
    std::cerr << "Failed to load lib from " << get_lib_path() << "\n";
    return;
  }

  std::cout << "Tyr to load sym's....\n";
  for (int i = 0; i < FUNC_NUMS; ++i) {
    std::cout << "Try to load " << g_func_name[i] << "\n";
    CHECK(auto ret_sym = dlsym(handle, g_func_name[i]));
    if (!ret_sym) {
      std::cerr << "Failed to load func " << g_func_name[i] << " from "
                << get_lib_path() << "\n";
    }
    __atomic_store_n(g_func_tb + i, ret_sym, __ATOMIC_RELAXED);
    std::cout << "Load " << g_func_name[i] << " success!\n";
  }
}

void load_library() {

  std::cout << "call " << __func__ << "\n";

  static std::once_flag _flag;
  std::call_once(_flag, init);
}

void test();

int main() {
  std::cout << "Test lazy load libs\n";

  test();

  return 0;
}

void test() {
#define TEST(Ty)                                                               \
  {                                                                            \
    Ty lhs = 12, rhs = 34;                                                     \
    Ty res = _add_##Ty(lhs, rhs);                                              \
    std::cout << "Test: " << typeid(res).name() << "\n";                       \
  }

  TEST(int);
  TEST(float);
  TEST(double);
}
