#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "galois.h"

// TODO: clean this up later
int dataShardCount;
int parityShardCount;
void *codingLoop;
int totalShardCount;
matrix_t *m;

matrix_t* vandermonde(int rows, int cols);

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
    //top = vandermonde.submatrix(0, 0, dataShards, dataShards);
    matrix_t *inverted = matrix_invert(top);

    return vandermonde.times(top.invert());
}

int rs(int rs_dataShardCount, int rs_parityShardCount, void *rs_codingLoop) {

    // We can have at most 256 shards total, as any more would
    // lead to duplicate rows in the Vandermonde matrix, which
    // would then lead to duplicate rows in the built matrix
    // below. Then any subset of the rows containing the duplicate
    // rows would be singular.
    if (256 < dataShardCount + parityShardCount) {
        fprintf(stderr, "too many shards - max is 256");
        exit(1);
    }

    dataShardCount = rs_dataShardCount;
    parityShardCount = rs_parityShardCount;
    codingLoop = rs_codingLoop;
    totalShardCount = dataShardCount + parityShardCount;
    matrix = buildMatrix(dataShardCount, totalShardCount);

    parityRows = new byte [parityShardCount] [];
    for (int i = 0; i < parityShardCount; i++) {
        parityRows[i] = matrix.getRow(dataShardCount + i);
    }
}
