// Copyright 2021 Ola Nordstrom

#include "galois.h"
#include "doctest.h"

TEST_CASE("galois multiply") {
    CHECK(12 == galois_multiply(3, 4));
    CHECK(21 == galois_multiply(7, 7));
    CHECK(41 == galois_multiply(23, 45));
}

TEST_CASE("galois exp") {
    CHECK(4 == galois_exp(2, 2));
    CHECK(235 ==  galois_exp(5, 20));
    CHECK(43 == galois_exp(13, 7));
}