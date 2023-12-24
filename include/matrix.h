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

matrix_t* matrix_dot(const matrix_t* A, const matrix_t* B);

void matrix_print(const matrix_t* m);

void matrix_sigmoid(matrix_t* m);

int matrix_argmax(const matrix_t* m);

void matrix_deepcopy(matrix_t* dst, matrix_t* src);

matrix_t* matrix_calc_activation(const matrix_t *a, const matrix_t *w, const matrix_t *b);

void matrix_destroy(matrix_t* mm);
#endif