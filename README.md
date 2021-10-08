# README

This is a C implementation of the Backblaze [Java Reed Solomon](https://github.com/Backblaze/JavaReedSolomon) encoding and decoding over an 8-bit Galois field. 

## TODO
- ~~change get_row to not allocate memory~~
- ~~free memory~~
- ~~change memory allocation to use cudaMalloc~~
- integrate Makefile.cuda into cmake
- figure out if copying rs.cpp to rs.cu is required or if there some nvcc flag that can do it
- impelement decoding
- add more tests
- cleanup tests to use strings (easier to read)
- separate the pure C from the few C++ functions in the implementation
- investigate move to kernel driver
- investigate additional CUDA speedups

## Build

```
cmake . && make       # to build the native code implementation
make -f Makefile.cuda # to build the Nvidia CUDA implementation
```
