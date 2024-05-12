cmake -Bbuild .
cmake --build build

BIN_PATH="./build/bin/test_load_library"

#ldd ${BIN_PATH=}
#${BIN_PATH=}

./build/bin/test_lazy_load_library
