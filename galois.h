// Copyright 2021 Ola Nordstrom

#ifndef GALOIS_H
#define GALOIS_H

#include <stdint.h>

typedef uint8_t BYTE;

void galois_init();
BYTE galois_add(BYTE a, BYTE b);
BYTE galois_subtract(BYTE a, BYTE b);
BYTE galois_multiply(BYTE a, BYTE b);
BYTE galois_divide(BYTE a, BYTE b);
BYTE galois_exp(BYTE a, int n);

int16_t* generateLogTable(int polynomial);
BYTE *generateExpTable(int16_t* logTable);
BYTE *generateMultiplicationTable();

#endif
