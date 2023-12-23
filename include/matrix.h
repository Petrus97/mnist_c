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

matrix_t* matrix_dot(matrix_t* A, matrix_t* B);

void matrix_print(matrix_t* m);

void matrix_sigmoid(matrix_t* m);

int matrix_argmax(const matrix_t* m);

void matrix_destroy(matrix_t* mm);
#endif