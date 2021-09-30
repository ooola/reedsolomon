#include <stdlib.h>
#include <stdio.h>
#include "rs.h"
#include "matrix.h"
#include "galois.h"

rs_t* rs_new()
{
    rs_t* r = (rs_t*) malloc(sizeof(rs_t));
    if (!r) {
        fprintf(stderr, "failed to allocate reed solomon struct, exiting.");
        exit(1);
    }
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
    size_t totalShardCount = dataShardCount + parityShardCount;
    r->m = buildMatrix(dataShardCount, totalShardCount);

    //parityRows = new byte [parityShardCount] [];
    /*
    r->parity_rows = 
    for (int i = 0; i < parityShardCount; i++) {
        parityRows[i] = matrix.getRow(dataShardCount + i);
    }
    */
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

    //byte [] [] outputs = new byte [parityShardCount] [];
    //System.arraycopy(shards, dataShardCount, outputs, 0, parityShardCount);
    BYTE* outputs = (BYTE*) calloc(1, r->parity_shards * byte_count);
    if (!outputs) {
        fprintf(stderr, "failed to allocate output memory, exiting...\n");
        exit(1);
    }
    // TODO: what about offset ???
    memcpy(outputs, shards + (r->data_shards * byte_count), (r->parity_shards * byte_count));

    code_some_shards(r, shards, outputs, offset, byte_count);
}

/**
 * ByteInputOutputExpCodingLoop
 */
void code_some_shards(rs_t* r, BYTE* shards, BYTE* outputs, int offset, int byte_count)
{
    /*
    wip
    for (int iByte = offset; iByte < offset + byte_count; iByte++) {
    {
        int iInput = 0;
        byte[] inputShard = inputs[iInput];
        byte inputByte = inputShard[iByte];
        for (int iOutput = 0; iOutput < outputCount; iOutput++) {
            byte[] outputShard = outputs[iOutput];
            byte[] matrixRow = matrixRows[iOutput];
            outputShard[iByte] = Galois.multiply(matrixRow[iInput], inputByte);
        }
    }

    for (int iInput = 1; iInput < inputCount; iInput++) {
        final byte[] inputShard = inputs[iInput];
        final byte inputByte = inputShard[iByte];
        for (int iOutput = 0; iOutput < outputCount; iOutput++) {
            final byte[] outputShard = outputs[iOutput];
            final byte[] matrixRow = matrixRows[iOutput];
            outputShard[iByte] ^= Galois.multiply(matrixRow[iInput], inputByte);
        }
    }
    */

}