#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef unsigned char BYTE;

typedef struct matrix {
    /**
     * The number of rows in the matrix.
     */
    int rows;

    /**
 * The number of columns in the matrix.
 */
    int columns;

    /**
 * The data in the matrix, in row major form.
 *
 * To get element (r, c): data[r][c]
 *
 * Because this this is computer science, and not math,
 * the indices for both the row and column start at 0.
 */
    int rows;
    int columns;
    BYTE *data;
} matrix_t;

/**
 * To use call 
 */

matrix_t* matrix_init(int initRows, int initColumns);
void matrix_set(matrix_t* m, int row, int column, BYTE data);

#endif
