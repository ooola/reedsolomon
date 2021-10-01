/*
 * =====================================================================================
 *
 *       Filename:  rs.h
 *
 *    Description:  jjj
 *
 *        Version:  1.0
 *        Created:  09/19/2021 14:07:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "matrix.h"

typedef struct _rs {
    int data_shards;
    int parity_shards; 
    int total_shards;
    matrix_t *m;
    int parity_row_count;
    int parity_row_size;
    matrix_t* parity_rows;
} rs_t;

rs_t* rs(int dataShardCount, int parityShardCount); // call this to make a new encoder
matrix_t* vandermonde(int rows, int cols);
matrix_t* buildMatrix(int dataShards, int totalShards);
void encode_parity(rs_t* r, BYTE* shards, int offset, int byte_count);
void code_some_shards(rs_t* r, BYTE* input_shards, int input_count, BYTE* outputs, int output_count, int offset, int byte_count);