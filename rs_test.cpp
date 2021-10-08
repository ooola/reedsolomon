// Copyright 2021 Ola Nordstrom

#include <iostream>
#include "rs.h"
#include "doctest.h"

TEST_CASE("test one encode") {
    rs_t* r = rs(5, 5);
    std::cout << " here's the matrix\n";
    matrix_print(r->m, false);

    BYTE shards[20] = {0, 1,
                       4, 5,
                       2, 3,
                       6, 7,
                       8, 9,
                       0, 0,
                       0, 0,
                       0, 0,
                       0, 0,
                       0, 0};

    encode_parity(r, shards, 0, 2);
    
    CHECK(shards[10] == 12);
    CHECK(shards[11] == 13);
    CHECK(shards[12] == 10);
    CHECK(shards[13] == 11);
    CHECK(shards[14] == 14);
    CHECK(shards[15] == 15);
    CHECK(shards[16] == 90);
    CHECK(shards[17] == 91);
    CHECK(shards[18] == 94);
    CHECK(shards[19] == 95);

    //TODO do implement isParityCorrect() function
}

TEST_CASE("test non uniform encode") {
    rs_t* r = rs(4, 2);
    std::cout << " here's the matrix\n";
    matrix_print(r->m, false);

    BYTE shards[12] = {0, 1,
                       4, 5,
                       2, 3,
                       6, 7,
                       0, 0,
                       0, 0};

    encode_parity(r, shards, 0, 2);
    
    CHECK(shards[8] == 44);
    CHECK(shards[9] == 45);
    CHECK(shards[10] == 40);
    CHECK(shards[11] == 41);
}