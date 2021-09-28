#ifndef GALOIS_H
#define GALOIS_H

#include <stdint.h>

//typedef char BYTE;
//typedef int8_t BYTE;
typedef uint8_t BYTE;
//typedef int16_t BYTE;

/**
 * To use call generateMultiplicationTable() 
 */

void galois_init();
BYTE add(BYTE a, BYTE b);
BYTE subtract(BYTE a, BYTE b);
BYTE multiply(BYTE a, BYTE b);
BYTE divide(BYTE a, BYTE b);
BYTE exp(BYTE a, int n);

int16_t* generateLogTable(int polynomial);
BYTE *generateExpTable(int16_t* logTable);
BYTE *generateMultiplicationTable();

BYTE *getLogTable();

#endif