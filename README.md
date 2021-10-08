#README

## TODO
- -change get_row to not allocate memory-
- -free memory-
- -change memory allocation to use cudaMalloc-
 

## Build

```
CUDA_HOME=/usr/lib/cuda
```

## Make code compatible
```
ubuntu@gc-awesome-franklin:~/reedsolomon$ make -f Makefile.cuda rs
CUDA_HOME=/usr/lib/cuda nvcc -lstdc++ -o rs -D USE_GPU rs.cu matrix.cpp galois.cpp util.cpp 
rs.cu(100): error: calling a __host__ function("fprintf") from a __global__ function("encode_parity") is not allowed

rs.cu(100): error: identifier "fprintf" is undefined in device code

rs.cu(100): error: identifier "stderr" is undefined in device code

rs.cu(101): error: calling a __host__ function("exit") from a __global__ function("encode_parity") is not allowed

rs.cu(101): error: identifier "exit" is undefined in device code

rs.cu(104): error: calling a __host__ function("fprintf") from a __global__ function("encode_parity") is not allowed

rs.cu(104): error: identifier "fprintf" is undefined in device code

rs.cu(104): error: identifier "stderr" is undefined in device code

rs.cu(105): error: calling a __host__ function("exit") from a __global__ function("encode_parity") is not allowed

rs.cu(105): error: identifier "exit" is undefined in device code

rs.cu(110): error: calling a __host__ function("code_some_shards") from a __global__ function("encode_parity") is not allowed

rs.cu(110): error: identifier "code_some_shards" is undefined in device code

12 errors detected in the compilation of "/tmp/tmpxft_00001635_00000000-8_rs.cpp1.ii".
```
