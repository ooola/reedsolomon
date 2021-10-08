// Copyright 2021 Ola Nordstrom
#ifndef RS_H
#define RS_H

#include "matrix.h"

typedef struct _rs {
    int data_shards;
    int parity_shards; 
    int total_shards;
    matrix_t* parity_rows;
    matrix_t *m;
} rs_t;

rs_t* rs(int dataShardCount, int parityShardCount); // call this to make a new encoder
void rs_free(rs_t* r);
matrix_t* vandermonde(int rows, int cols);
matrix_t* buildMatrix(int dataShards, int totalShards);
void encode_parity(rs_t* r, BYTE *shards, int offset, int byte_count);
#ifdef USE_GPU
__global__
void code_some_shards(rs_t* r, BYTE* input_shards, int input_count, BYTE* outputs, int output_count, int offset, int byte_count);
#else
void code_some_shards(rs_t* r, BYTE* input_shards, int input_count, BYTE* outputs, int output_count, int offset, int byte_count);
#endif

#endif