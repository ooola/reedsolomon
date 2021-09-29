#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <string>
#include "galois.h"

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
     * To get an element compute the offset as follows:
     * 
     *     int offset = (r * (m->rows)) + c;
     *     return m->data[offset];
     */
    BYTE *data;
} matrix_t;

/**
 * To use call 
 */

matrix_t* matrix_init(int initRows, int initColumns);
matrix_t* matrix(int rows, int columns, BYTE *initData);
matrix_t* matrix_identity(int size);
void matrix_print(matrix_t *m, bool hex);
void matrix_set(matrix_t* m, int row, int column, BYTE data);
BYTE matrix_get(matrix_t* m, int row, int column);
matrix_t* matrix_times(matrix_t* m, matrix_t* right);
matrix_t* augment(matrix_t *m, matrix_t* right);
matrix_t* matrix_submatrix(matrix_t* m, int rmin, int cmin, int rmax, int cmax);
void matrix_gaussian_elemination(matrix_t* m);
matrix_t *matrix_invert(matrix_t *m); 
void matrix_swap_rows(matrix_t* m, int r1, int r2);
bool matrix_equals(matrix_t* a, matrix_t* b);
std::string matrix_string(matrix_t* m);

#endif
