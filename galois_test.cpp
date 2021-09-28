
#include "galois.h"
#include "doctest.h"

TEST_CASE("galois multiply") {
    CHECK(12 == multiply(3, 4));
    CHECK(21 == multiply(7, 7));
    CHECK(41 == multiply(23, 45));
}

TEST_CASE("galois exp") {
    CHECK(4 == exp(2, 2));
    CHECK(235 ==  exp(5, 20));
    CHECK(43 == exp(13, 7));
}

/*
TEST_CASE("test generate log table") {
    int16_t *test_log_table = generateLogTable(29);
    //BYTE *logTable = getLogTable();
    int16_t *logTable = (int16_t *)getLogTable();
    for (int i = 0; i < 256; i++) {
        INFO("checking i: ", i);
        CHECK(test_log_table[i] == logTable[i]);
    }
}
*/

/*
TEST_CASE("testMultiplicationTable") {
    BYTE *table = generateMultiplicationTable();
    byte [] [] table = Galois.MULTIPLICATION_TABLE;
    for (int a = -128; a < 128; a++) {
        for (int b = -128; b < 128; b++) {
            CHECK(4 == exp(2, 2));
            assertEquals(Galois.multiply((byte) a, (byte) b), table[a & 0xFF][b & 0xFF]);
        }
    }
}
*/

