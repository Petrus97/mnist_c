#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct matrix_t
{
    uint32_t rows;
    uint32_t cols;
    float* data;
} matrix_t;

matrix_t* matrix_create(uint32_t rows, uint32_t cols);
void matrix_destroy(matrix_t* mm);
#endif