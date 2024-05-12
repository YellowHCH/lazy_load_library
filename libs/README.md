* Generate libs

```bash
cd {current dir}
cmake -Bbuild .
cmake --build build  --target all
cmake --build build  --target install
```
* Run test

```bash
./build/bin/test_lazy_lib
```

