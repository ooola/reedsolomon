#include "matrix.h"
#include "doctest.h"

TEST_CASE("matrix identity test") {
    matrix_t *m = matrix_identity(4);
    /**
     * matrix should be as follows
     * [1 0 0 0]
     * [0 1 0 0]
     * [0 0 1 0]
     * [0 0 0 1]
     */
    CHECK(4 == m->rows);
    CHECK(4 == m->columns);

    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(0 == matrix_get(m, 0, 1));
    CHECK(0 == matrix_get(m, 0, 2));
    CHECK(0 == matrix_get(m, 0, 3));

    CHECK(0 == matrix_get(m, 1, 0));
    CHECK(1 == matrix_get(m, 1, 1));
    CHECK(0 == matrix_get(m, 1, 2));
    CHECK(0 == matrix_get(m, 1, 3));

    CHECK(0 == matrix_get(m, 2, 0));
    CHECK(0 == matrix_get(m, 2, 1));
    CHECK(1 == matrix_get(m, 2, 2));
    CHECK(0 == matrix_get(m, 2, 3));

    CHECK(0 == matrix_get(m, 3, 0));
    CHECK(0 == matrix_get(m, 3, 1));
    CHECK(0 == matrix_get(m, 3, 2));
    CHECK(1 == matrix_get(m, 3, 3));
}

TEST_CASE("submatrix test") {
    matrix_t *m = matrix_identity(4);
    /**
     * matrix should be as follows
     * [1 0 0 0]
     * [0 1 0 0]
     * [0 0 1 0]
     * [0 0 0 1]
     */

    matrix_t *s = matrix_submatrix(m, 0, 0, 2, 2);
    /**
     * submatrix should be as follows
     * [1 0]
     * [0 1]
     */
    CHECK(2 == s->rows);
    CHECK(2 == s->columns);

    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(0 == matrix_get(m, 0, 1));

    CHECK(0 == matrix_get(m, 1, 0));
    CHECK(1 == matrix_get(m, 1, 1));
}

TEST_CASE("submatrix test 2") {
    BYTE d[24] = { 1,   0,  0,  0,
                   0,   1,  0,  0,
                   0,   0,  1,  0,
                   0,   0,  0,  1,
                   27, 28, 18, 20,
                   28, 27, 20, 18 };
    matrix_t *m = matrix(6, 4, d);
    matrix_t *s = matrix_submatrix(m, 4, 0, 6, 4);
    CHECK(2 == s->rows);
    CHECK(4 == s->columns);

    CHECK(27 == matrix_get(s, 0, 0));
    CHECK(28 == matrix_get(s, 0, 1));
    CHECK(18 == matrix_get(s, 0, 2));
    CHECK(20 == matrix_get(s, 0, 3));
    CHECK(28 == matrix_get(s, 1, 0));
    CHECK(27 == matrix_get(s, 1, 1));
    CHECK(20 == matrix_get(s, 1, 2));
    CHECK(18 == matrix_get(s, 1, 3));
}

TEST_CASE("matrix swap test") {
    matrix_t *m = matrix_identity(4);
    // * matrix should be as follows
    // * [1 0 0 0]
    // * [0 1 0 0]
    // * [0 0 1 0]
    // * [0 0 0 1]
    CHECK(4 == m->rows);
    CHECK(4 == m->columns);

    matrix_swap_rows(m, 1, 3);
    /**
     * matrix should be as follows
     * [1 0 0 0]
     * [0 0 0 1]
     * [0 0 1 0]
     * [0 1 0 0]
     */

    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(0 == matrix_get(m, 0, 1));
    CHECK(0 == matrix_get(m, 0, 2));
    CHECK(0 == matrix_get(m, 0, 3));

    CHECK(0 == matrix_get(m, 1, 0));
    CHECK(0 == matrix_get(m, 1, 1));
    CHECK(0 == matrix_get(m, 1, 2));
    CHECK(1 == matrix_get(m, 1, 3));

    CHECK(0 == matrix_get(m, 2, 0));
    CHECK(0 == matrix_get(m, 2, 1));
    CHECK(1 == matrix_get(m, 2, 2));
    CHECK(0 == matrix_get(m, 2, 3));

    CHECK(0 == matrix_get(m, 3, 0));
    CHECK(1 == matrix_get(m, 3, 1));
    CHECK(0 == matrix_get(m, 3, 2));
    CHECK(0 == matrix_get(m, 3, 3));

    matrix_print(m, true);
}

TEST_CASE("matrix swap test") {
    BYTE md[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    matrix_t *m = matrix(4, 2, md);
    // matrix should be as follows
    // [1 2]
    // [3 4]
    // [5 6]
    // [7 8]
    CHECK(4 == m->rows);
    CHECK(2 == m->columns);
    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(2 == matrix_get(m, 0, 1));
    CHECK(3 == matrix_get(m, 1, 0));
    CHECK(4 == matrix_get(m, 1, 1));
    CHECK(5 == matrix_get(m, 2, 0));
    CHECK(6 == matrix_get(m, 2, 1));
    CHECK(7 == matrix_get(m, 3, 0));
    CHECK(8 == matrix_get(m, 3, 1));

    matrix_swap_rows(m, 1, 3);
    // matrix should be as follows
    // [1 2]
    // [7 8]
    // [5 6]
    // [3 4]

    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(2 == matrix_get(m, 0, 1));
    CHECK(7 == matrix_get(m, 1, 0));
    CHECK(8 == matrix_get(m, 1, 1));
    CHECK(5 == matrix_get(m, 2, 0));
    CHECK(6 == matrix_get(m, 2, 1));
    CHECK(3 == matrix_get(m, 3, 0));
    CHECK(4 == matrix_get(m, 3, 1));
}


TEST_CASE("matrix test") {
    BYTE d[9] = {56, 23, 98, 3, 100, 200, 45, 201, 123};
    matrix_t *m = matrix(3, 3, d);
    /**
     * matrix should be as follows
     * [56,  23,  98]
     * [ 3, 100, 200]
     * [45, 201, 123]
     */
    CHECK(3 == m->rows);
    CHECK(3 == m->columns);

    CHECK(56 == matrix_get(m, 0, 0));
    CHECK(100 == matrix_get(m, 1, 1));
    CHECK(123 == matrix_get(m, 2, 2));

    matrix_print(m, false);
}

TEST_CASE("matrix multiply") {
    BYTE m1d[9] = {1, 2, 3, 4};
    matrix_t *m1 = matrix(2, 2, m1d);
    BYTE m2d[9] = {5, 6, 7, 8};
    matrix_t *m2 = matrix(2, 2, m2d);

    matrix_t *actual = matrix_times(m1, m2);
    //assertEquals("[[11, 22], [19, 42]]", actual.toString());
    CHECK(11 == matrix_get(actual, 0, 0));
    CHECK(22 == matrix_get(actual, 0, 1));
    CHECK(19 == matrix_get(actual, 1, 0));
    CHECK(42 == matrix_get(actual, 1, 1));
    matrix_print(actual, false);
}


TEST_CASE("non square matrix test 1") {
    BYTE md[9] = {1, 2, 3, 4, 5, 6, 7, 8};
    matrix_t *m = matrix(2, 4, md);

    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(2 == matrix_get(m, 0, 1));
    CHECK(3 == matrix_get(m, 0, 2));
    CHECK(4 == matrix_get(m, 0, 3));
    CHECK(5 == matrix_get(m, 1, 0));
    CHECK(6 == matrix_get(m, 1, 1));
    CHECK(7 == matrix_get(m, 1, 2));
    CHECK(8 == matrix_get(m, 1, 3));
    matrix_print(m, false);
}

TEST_CASE("non square matrix test 2") {
    BYTE md[9] = {1, 2, 3, 4, 5, 6, 7, 8};
    matrix_t *m = matrix(4, 2, md);

    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(2 == matrix_get(m, 0, 1));
    CHECK(3 == matrix_get(m, 1, 0));
    CHECK(4 == matrix_get(m, 1, 1));
    CHECK(5 == matrix_get(m, 2, 0));
    CHECK(6 == matrix_get(m, 2, 1));
    CHECK(7 == matrix_get(m, 3, 0));
    CHECK(8 == matrix_get(m, 3, 1));
    matrix_print(m, false);
}

TEST_CASE("matrix inverse test") {
    BYTE d[9] = {56, 23, 98, 3, 100, 200, 45, 201, 123};
    matrix_t *m = matrix(3, 3, d);
    /**
     * matrix should be as follows
     * [56,  23,  98]
     * [ 3, 100, 200]
     * [45, 201, 123]
     */
    CHECK(3 == m->rows);
    CHECK(3 == m->columns);

    // basic checks
    CHECK(56 == matrix_get(m, 0, 0));
    CHECK(200 == matrix_get(m, 1, 2));
    CHECK(201 == matrix_get(m, 2, 1));

    matrix_print(m, false);

    matrix_t* inverted = matrix_invert(m);
    INFO("Inverted matrix is:");
    matrix_print(inverted, false);
    // "[[175, 133, 33], [130, 13, 245], [112, 35, 126]]",
    CHECK(175 == matrix_get(inverted, 0, 0));
    CHECK(133 == matrix_get(inverted, 0, 1));
    CHECK(33 == matrix_get(inverted, 0, 2));
    CHECK(130 == matrix_get(inverted, 1, 0));
    CHECK(13 == matrix_get(inverted, 1, 1));
    CHECK(245 == matrix_get(inverted, 1, 2));
    CHECK(112 == matrix_get(inverted, 2, 0));
    CHECK(35 == matrix_get(inverted, 2, 1));
    CHECK(126 == matrix_get(inverted, 2, 2));

    // inverted m times itself should be identity matrix
    matrix_t* t = matrix_times(m, inverted);
    matrix_t* i = matrix_identity(3);
    CHECK(matrix_equals(t, i) == true);
}

TEST_CASE("matrix inverse2 test") {
    BYTE d[25] = { 1, 0, 0, 0, 0, 
                   0, 1, 0, 0, 0,
                   0, 0, 0, 1, 0,
                   0, 0, 0, 0, 1,
                   7, 7, 6, 6, 1 };
    matrix_t *m = matrix(5, 5, d);
     // matrix should be as follows
     // [ 1, 0, 0, 0, 0 ]
     // [ 0, 1, 0, 0, 0 ]
     // [ 0, 0, 0, 1, 0 ]
     // [ 0, 0, 0, 0, 1 ]
     // [ 7, 7, 6, 6, 1 ]
     //
    CHECK(5 == m->rows);
    CHECK(5 == m->columns);

    // basic checks
    CHECK(1 == matrix_get(m, 0, 0));
    CHECK(7 == matrix_get(m, 4, 0));
    CHECK(6 == matrix_get(m, 4, 2));

    matrix_print(m, false);
    INFO(matrix_string(m));

    INFO("Matrix to invert: ", matrix_string(m));
    matrix_t* inverted = matrix_invert(m);
    INFO("Inverted matrix is: ", matrix_string(inverted));
    // [[1, 0, 0, 0, 0],
    //  [0, 1, 0, 0, 0],
    //  [123, 123, 1, 122, 122],
    //  [0, 0, 1, 0, 0],
    //  [0, 0, 0, 1, 0]]
    CHECK(1 == matrix_get(inverted, 0, 0));
    CHECK(0 == matrix_get(inverted, 0, 1));
    CHECK(0 == matrix_get(inverted, 0, 2));
    CHECK(0 == matrix_get(inverted, 0, 3));
    CHECK(0 == matrix_get(inverted, 0, 4));

    CHECK(0 == matrix_get(inverted, 1, 0));
    CHECK(1 == matrix_get(inverted, 1, 1));
    CHECK(0 == matrix_get(inverted, 1, 2));
    CHECK(0 == matrix_get(inverted, 1, 3));
    CHECK(0 == matrix_get(inverted, 1, 4));

    CHECK(123 == matrix_get(inverted, 2, 0));
    CHECK(123 == matrix_get(inverted, 2, 1));
    CHECK(1 == matrix_get(inverted, 2, 2));
    CHECK(122 == matrix_get(inverted, 2, 3));
    CHECK(122 == matrix_get(inverted, 2, 4));

    CHECK(0 == matrix_get(inverted, 3, 0));
    CHECK(0 == matrix_get(inverted, 3, 1));
    CHECK(1 == matrix_get(inverted, 3, 2));
    CHECK(0 == matrix_get(inverted, 3, 3));
    CHECK(0 == matrix_get(inverted, 3, 4));

    CHECK(0 == matrix_get(inverted, 4, 0));
    CHECK(0 == matrix_get(inverted, 4, 1));
    CHECK(0 == matrix_get(inverted, 4, 2));
    CHECK(1 == matrix_get(inverted, 4, 3));
    CHECK(0 == matrix_get(inverted, 4, 4));
}

TEST_CASE("matrix test get row") {
    BYTE d[25] = { 1, 0, 0, 0, 0, 
                   0, 1, 0, 0, 0,
                   0, 0, 0, 1, 0,
                   0, 0, 0, 0, 1,
                   7, 7, 6, 6, 1 };
    matrix_t *m = matrix(5, 5, d);
     // matrix should be as follows
     // [ 1, 0, 0, 0, 0 ]
     // [ 0, 1, 0, 0, 0 ]
     // [ 0, 0, 0, 1, 0 ]
     // [ 0, 0, 0, 0, 1 ]
     // [ 7, 7, 6, 6, 1 ]
     //
    CHECK(5 == m->rows);
    CHECK(5 == m->columns);
    BYTE *row = matrix_get_row(m, 4);
    CHECK(7 == matrix_get(m, 4, 0));
    CHECK(7 == matrix_get(m, 4, 1));
    CHECK(6 == matrix_get(m, 4, 2));
    CHECK(6 == matrix_get(m, 4, 3));
    CHECK(1 == matrix_get(m, 4, 4));
}