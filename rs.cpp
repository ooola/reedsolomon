#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "rs.h"
#include "matrix.h"
#include "galois.h"

rs_t* rs_new()
{
    rs_t* r = (rs_t*) allocate_shared_memory_or_exit(sizeof(rs_t));
    return r;
}

/**
 * Create a Vandermonde matrix, which is guaranteed to have the
 * property that any subset of rows that forms a square matrix
 * is invertible.
 *
 * @param rows Number of rows in the result.
 * @param cols Number of columns in the result.
 * @return A Matrix.
 */
matrix_t* vandermonde(int rows, int cols) {
    matrix_t* result = matrix_init(rows, cols);
    for (BYTE r = 0; r < rows; r++) {
        for (BYTE c = 0; c < cols; c++) {
            matrix_set(result, r, c, exp((BYTE)r, c));
        }
    }
    return result;
}

matrix_t* buildMatrix(int dataShards, int totalShards) {
    // Start with a Vandermonde matrix.  This matrix would work,
    // in theory, but doesn't have the property that the data
    // shards are unchanged after encoding.
    matrix_t* vm = vandermonde(totalShards, dataShards);

    // Multiple by the inverse of the top square of the matrix.
    // This will make the top square be the identity matrix, but
    // preserve the property that any square subset of rows is
    // invertible.
    matrix_t *top = matrix_submatrix(vm, 0, 0, dataShards, dataShards);
    matrix_t *inverted = matrix_invert(top);

    matrix_t *rv = matrix_times(vm, inverted);
    return rv;
}

rs_t* rs(int dataShardCount, int parityShardCount) {

    rs_t* r = rs_new();

    // We can have at most 256 shards total, as any more would
    // lead to duplicate rows in the Vandermonde matrix, which
    // would then lead to duplicate rows in the built matrix
    // below. Then any subset of the rows containing the duplicate
    // rows would be singular.
    if (256 < dataShardCount + parityShardCount) {
        fprintf(stderr, "too many shards - max is 256");
        exit(1);
    }

    r->data_shards = dataShardCount;
    r->parity_shards = parityShardCount;
    r->total_shards = dataShardCount + parityShardCount;
    r->m = buildMatrix(dataShardCount, r->total_shards);
    printf("here is the matrix\n");
    matrix_print(r->m, false);

    r->parity_rows = matrix_submatrix(r->m, dataShardCount, 0, r->m->rows, r->m->columns);

    return r;
}

/**
 * encodes the parity for the set of shards
 * offset in the index of the first byte in each shard
 * byte_count is the number of bytes in each shard
 */
void encode_parity(rs_t* r, BYTE *shards, int offset, int byte_count)
{
    if (!shards) {
        fprintf(stderr, "missing shards");
        exit(1);
    }
    if (offset < 0 || byte_count < 0) {
        fprintf(stderr, "invalid encoding params");
        exit(1);
    }

    BYTE* outputs = shards + (r->data_shards * byte_count);

    code_some_shards(r, shards, r->data_shards, outputs, r->parity_shards, offset, byte_count);
}

/**
 * ByteOutputInputExpCodingLoop
 * r contains the parity rows
 * // Do the coding.
   codingLoop.codeSomeShards(
           parityRows,
           shards, dataShardCount,
           outputs, parityShardCount,
           offset, byteCount);

     public void codeSomeShards(
            byte[][] matrixRows, 
            byte[][] inputs, int inputCount,
            byte[][] outputs, int outputCount,
            int offset, int byteCount) {
 */
void code_some_shards(rs_t* r, BYTE* input_shards, int input_count, 
                      BYTE* outputs, int output_count, int offset, int byte_count)
{
    matrix_t* m = r->parity_rows; // parity rows
    for (int iByte = offset; iByte < offset + byte_count; iByte++) {
        for (int iOutput = 0; iOutput < output_count; iOutput++) {
            // matrix_rows are from the matrix embedded in rs;
            //byte [] matrixRow = matrixRows[iOutput];
            BYTE* matrixRow = matrix_get_row(m, iOutput);
            int value = 0;
            for (BYTE iInput = 0; iInput < input_count; iInput++) {
                //BYTE = input_shards[iInput]
                BYTE a = matrixRow[iInput];

                // inputs[iInput][iByte];
                // calculate the equivalent byte location
                int addr = (iInput * byte_count) + iByte;
                BYTE b = input_shards[addr];
                value ^= multiply(a, b);
                //value ^= multiply(matrixRow[iInput], inputs[iInput][iByte]);
            }
            int output_addr = (iOutput * byte_count) + iByte;
            outputs[output_addr] =  value;
        }
    }
}