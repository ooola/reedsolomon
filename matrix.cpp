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
#include "matrix.h"

void *matrix_new(int rows, int columns) 
{
    struct matrix *m = malloc(sizeof(struct matrix));
    if (m == NULL) {
        fprintf(stderr, "malloc failed");
        exit(1);
    }
}
