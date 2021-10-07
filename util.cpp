#include <stdlib.h>
#include <stdio.h>
#include "util.h"

/**
 * allocates memory shared between the GPU and Host so that it can be accessesed from both
 */
void* allocate_shared_memory_or_exit(size_t s)
{
    void *mem;
#ifdef USE_GPU
    cudaError_t e = cudaMallocManaged((void**)&mem, s);
    if (e != cudaSuccess) {
        fprintf(stderr, "failed to allocate Cuda managed memory, exiting...");
        exit(1);
    }
#else
    mem = (void*) calloc(1, s);
    if (!mem) {
        fprintf(stderr, "failed to allocate memory, exiting...");
        exit(1);
    }
#endif
    return mem;
}

/**
 * frees the passed in memory
 */
void free_memory(void *mem) {
#ifdef USE_GPU
    cudaFree(mem);
#else
    free(mem);
#endif
}