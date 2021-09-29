/*
 * =====================================================================================
 *
 *       Filename:  matrix.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/19/2021 14:19:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "matrix.h"

/**
 * Initialize a matrix of zeros.
 *
 * @param initRows The number of rows in the matrix.
 * @param initColumns The number of columns in the matrix.
 */
matrix_t* matrix_init(int initRows, int initColumns) {
    matrix_t* m = (matrix_t *) calloc(sizeof(matrix_t), 1);
    if (!m) {
        fprintf(stderr, "failed to allocate matrix");
        exit(1);
    }

    m->columns = initColumns;
    m->rows = initRows;

    size_t count = initRows * initColumns;
    m->data = (BYTE *) calloc(count, 1);
    if (!m->data) {
        fprintf(stderr, "failed to allocate matrix data");
        exit(1);
    }
    return m;
}

/**
 * Initializes a matrix with the given row-major data.
 */
matrix_t* matrix(int rows, int columns, BYTE *initData) {
    matrix_t* m = matrix_init(rows, columns);
    /* note that we could just do a memcpy() here but we'll keep it readble
     * and let's hope hte compiler makes it fast */
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            int offset = (r * (m->columns)) + c;
            matrix_set(m, r, c, initData[offset]);
        }
    }
    return m;
}

/**
 * Returns an identity matrix of the given size.
 */
matrix_t* matrix_identity(int size) {
    matrix_t* m = matrix_init(size, size);
    for (int i = 0; i < size; i++) {
        matrix_set(m, i, i, 1);
    }
    return m;
}

/**
 * Returns a human-readable string of the matrix contents.
 *
 * Example: [[1, 2], [3, 4]]
 * 
 * TODO figure this out
 * print( )
 */

/**
 * Prints matrix
 *
 * Example:
 *    00 01 02
 *    03 04 05
 *    06 07 08
 *    09 0a 0b
 */
void matrix_print(matrix_t *m, bool hex) {
    if (!m) {
        fprintf(stderr, "matrix is null, exiting...\n");
        exit(1);
    }
    for (size_t r = 0; r < m->rows; r++) {
        for (size_t c = 0; c < m->columns; c++) {
            if (hex) {
                printf("0x%02X ", matrix_get(m, r, c));
            } else {
                printf("%03d ", matrix_get(m, r, c));
            }
        }
        printf("\n");
    }
}

/**
 * Returns the value at row r, column c.
 */
BYTE matrix_get(matrix_t* m, int r, int c) {
    if (r < 0 || m->rows <= r) {
        fprintf(stderr, "Row index out of range: %d\n", r);
        std::cout << "\nmatrix\n" << matrix_string(m) << "\n";
        exit(1);
    }
    if (c < 0 || m->columns <= c) {
        fprintf(stderr, "Column index out of range");
        exit(1);
    }
    int offset = ((m->columns) * r) + c;
    return m->data[offset];
}

/**
 * Sets the value at row r, column c.
 */
void matrix_set(matrix_t* m, int r, int c, BYTE value) {
    if (r < 0 || m->rows <= r) {
        fprintf(stderr, "Row index out of range");
        exit(1);
    }
    if (c < 0 || m->columns <= c) {
        fprintf(stderr, "Column index out of range");
        exit(1);
    }
    int offset = ((m->columns) * r) + c;
    m->data[offset] = value;
}

/**
 * Returns true iff this matrix is identical to the other.
 * TODO
 */

/**
 * Multiplies this matrix (the one on the left) by another
 * matrix (the one on the right).
 */
matrix_t* matrix_times(matrix_t* m, matrix_t* right) {
    if (m->columns != right->rows) {
        fprintf(stderr, "Columns on left is different than rows on right");
        exit(1);
    }
    matrix_t* result = matrix_init(m->rows, right->columns);
    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < right->columns; c++) {
            BYTE value = 0;
            for (int i = 0; i < m->columns; i++) {
                //value ^= Galois.multiply(get(r, i), right.get(i, c));
                value ^= multiply(matrix_get(m, r, i), matrix_get(right, i, c));
            }
            matrix_set(result, r, c, value);
        }
    }
    return result;
}

/**
 * Returns the concatenation of this matrix m and the matrix on the right.
 * Caller must free the resulting matrix.
 */

matrix_t* augment(matrix_t *m, matrix_t* right) {
    if (!m || !right) {
        fprintf(stderr, "augment passed null matricies, exiting...");
        exit(1);
    }
    if (m->rows != right->rows) {
        fprintf(stderr, "Matrices don't have the same number of rows, exiting...");
        exit(1);
    }
    matrix_t *result = matrix_init(m->rows, m->columns + right->columns);
    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->columns; c++) {
            //result.data[r][c] = data[r][c];
            BYTE data = matrix_get(m, r, c);
            matrix_set(result, r, c, data);
        }
        for (int c = 0; c < right->columns; c++) {
            //result.data[r][columns + c] = right.data[r][c];
            BYTE data = matrix_get(right, r, c);
            int column = m->columns + c;
            matrix_set(result, r, column, data);
        }
        matrix_print(result, false);
    }
    /*
    int result_row = 0;
    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->columns; c++) {
            //result.data[r][c] = data[r][c];
            BYTE data = matrix_get(m, r, c);
            matrix_set(result, result_row, c, data); // TODO this row changes - figure out the math!!!
        }
        matrix_print(result, false); // TODO 2 - fix this printing now that ^^^ is fixed.
        result_row++;
    }
    */
    matrix_print(result, false);
    return result;
}

/**
 * Returns a part of matrix m.
 * TODO
 */
matrix_t* matrix_submatrix(matrix_t* m, int rmin, int cmin, int rmax, int cmax) {
    if (!m) {
        fprintf(stderr, "matrix is null");
        exit(1);
    }
    matrix_t* result = matrix_init(rmax - rmin, cmax - cmin);
    for (int r = rmin; r < rmax; r++) {
        for (int c = cmin; c < cmax; c++) {
            //result.data[r - rmin][c - cmin] = data[r][c];
            BYTE data = matrix_get(m, r, c);
            matrix_set(result, r - rmin, c - cmin, data);
        }
    }
    return result;
}

/**
 * Returns one row of the matrix as a byte array.
 * TODO
 */
/*
BYTE* getRow(int row) {
    byte [] result = new byte [columns];
    for (int c = 0; c < columns; c++) {
        result[c] = get(row, c);
    }
    return result;
}
*/

/**
 * Exchanges two rows in the matrix.
 */
void matrix_swap_rows(matrix_t* m, int r1, int r2) {
    if (!m || r1 == r2) {
        fprintf(stderr, "Invalid matrix or rows passed to matrix_swap_rows");
        exit(1);
    }
    if (r1 < 0 || m->rows <= r1 || r2 < 0 || m->rows <= r2) {
        fprintf(stderr, "Row index out of range");
        std::cout << matrix_string(m) << "\n";
        exit(1);
    }
    for (size_t c = 0; c < m->columns; c++)
    {
        // use the xor trick to swap, memcpy may be faster but the compiler can deal with that
        int r1_offset = ((m->columns) * r1) + c;
        int r2_offset = ((m->columns) * r2) + c;
        m->data[r1_offset] = m->data[r1_offset] ^ m->data[r2_offset];
        m->data[r2_offset] = m->data[r1_offset] ^ m->data[r2_offset];
        m->data[r1_offset] = m->data[r1_offset] ^ m->data[r2_offset];
    }
}

/**
 * Returns the inverse of this matrix.
 *
 * exits when the matrix is singular and doesn't have an inverse.
 * 
 * caller must free the inverted matrix
 */
matrix_t *matrix_invert(matrix_t *m) {
    // Sanity check.
    if (m->rows != m->columns) {
        fprintf(stderr, "Only square matrices can be inverted");
        exit(1);
    }

    // Create a working matrix by augmenting this one with
    // an identity matrix on the right.
    matrix_t *identity = matrix_identity(m->rows);
    matrix_print(identity, false);
    matrix_t *work = augment(m, identity);
    matrix_print(work, false);

    // Do Gaussian elimination to transform the left half into
    // an identity matrix.
    //work.gaussianElimination();
    matrix_gaussian_elemination(work);
    matrix_print(work, false);

    // The right half is now the inverse.
    //return work.submatrix(0, rows, columns, columns * 2);
    return matrix_submatrix(work, 0, m->rows, m->columns, m->columns * 2);
}

/**
 * Does the work of matrix inversion.
 *
 * Assumes that this is an r by 2r matrix.
 */
 void matrix_gaussian_elemination(matrix_t *m) {
    // Clear out the part below the main diagonal and scale the main
    // diagonal to be 1.
    for (int r = 0; r < m->rows; r++) {
        // If the element on the diagonal is 0, find a row below
        // that has a non-zero and swap them.
        if (matrix_get(m, r, r) == (BYTE) 0) {
            for (int rowBelow = r + 1; rowBelow < m->rows; rowBelow++) {
                //if (data[rowBelow][r] != 0) {
                if (matrix_get(m, rowBelow, r) != 0) {
                    matrix_swap_rows(m, r, rowBelow);
                    break;
                }
            }
        }
        // If we couldn't find one, the matrix is singular.
        if (matrix_get(m, r, r) == (BYTE) 0) {
            fprintf(stderr, "Matrix is singular");
            exit(1);
        }
        // Scale to 1.
        if (matrix_get(m, r, r) != (BYTE) 1) {
            BYTE scale = divide(1, matrix_get(m, r, r));
            for (int c = 0; c < m->columns; c++) {
                matrix_set(m, r, c, multiply(matrix_get(m, r, c), scale));
            }
        }
        // Make everything below the 1 be a 0 by subtracting
        // a multiple of it.  (Subtraction and addition are
        // both exclusive or in the Galois field.)
        for (int rowBelow = r + 1; rowBelow < m->rows; rowBelow++) {
            if (matrix_get(m, rowBelow, r) != (BYTE) 0) {
                BYTE scale = matrix_get(m, rowBelow, r);
                for (int c = 0; c < m->columns; c++) {
                    //data[rowBelow][c] ^= Galois.multiply(scale, data[r][c]);
                    BYTE v = matrix_get(m, rowBelow, c);
                    v ^= multiply(scale, matrix_get(m, r, c));
                    matrix_set(m, rowBelow, c, v);
                }
            }
        }
    }

    // Now clear the part above the main diagonal.
    for (int d = 0; d < m->rows; d++) {
        for (int rowAbove = 0; rowAbove < d; rowAbove++) {
            if (matrix_get(m, rowAbove, d) != (BYTE) 0) {
                BYTE scale = matrix_get(m, rowAbove, d);
                for (int c = 0; c < m->columns; c++) {
                    //data[rowAbove][c] ^= Galois.multiply(scale, data[d][c]);
                    BYTE v = matrix_get(m, rowAbove, c);
                    v ^= multiply(scale, matrix_get(m, d, c));
                    matrix_set(m, rowAbove, c, v);
                }
            }
        }
    }
}

bool matrix_equals(matrix_t* a, matrix_t* b) {
    if (!a || !b) {
        return false;
    }

    if (a->columns != b->columns || a->columns != b->columns) {
        return false;
    }

    // probably should do this with memcmp but no premature optimizations
    for (size_t r = 0; r < a->rows; r++)
    {
        for (size_t c = 0; c < a->columns; c++)
        {
            if (matrix_get(a, r, c) != matrix_get(b, r, c)) {
                return false;
            }
        }
    }
    return true;
}

std::string matrix_string(matrix_t* m) {
    std::string s = "";
    for (size_t r = 0; r < m->rows; r++)
    {
        for (size_t c = 0; c < m->columns; c++)
        {
            s += " " + std::to_string(matrix_get(m, r, c));
        }
        s += "\n";
    }
    return s;
}