/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  jj
 *
 *        Version:  1.0
 *        Created:  09/19/2021 14:02:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#include "galois.h"

void multiplication_test() {
    if (multiply(3, 4) != 12) {
        fprintf(stderr, "galMultiply(3, 4) != 12");
        exit(1);
	}
    if (multiply(7, 7) != 21) {
        fprintf(stderr, "galMultiply(7, 7) != 21");
        exit(1);
	}
    if (multiply(23, 45) != 21) {
        fprintf(stderr, "galMultiply(23, 45) != 21");
        exit(1);
	}
}

int main(int argc, char *argv[]) {
    galois_init();
    multiplication_test();
    
    return 0;
}
