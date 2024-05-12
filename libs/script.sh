cmake -Bbuild .
cmake --build build --target install

./build/bin/test_lazy_lib
