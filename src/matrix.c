#include "matrix.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Create a matrix storing in the data field the 1D array-
 * The datatype stored is float.
 * It's a 1D array of dim rows x cols.
 * You access the array data[(i*cols)+j]
 * 
 * @param rows number of rows
 * @param cols number of cols
 * @return matrix_t* pointer to matrix
 */
matrix_t* matrix_create(uint32_t rows, uint32_t cols)
{
    matrix_t* mm = (matrix_t*)calloc(1, sizeof(matrix_t));
    mm->rows = rows;
    mm->cols = cols;
    // created as 1D array, index as data[(i*cols) + j]
    mm->data = (float*)calloc(mm->rows * mm->cols, sizeof(float));
    return mm;
}

matrix_t* matrix_dot(matrix_t* A, matrix_t* B)
{
    if(A->cols != B->rows)
    {
        printf("Dimensions mistmatch!\n");
        return NULL;
    }
    uint32_t common_dim = A->cols;
    matrix_t* C = matrix_create(A->rows, B->cols);
    for (size_t i = 0; i < A->rows; i++)
    {
        for (size_t j = 0; j < B->cols; j++)
        {
            float sum = 0.0;
            for (size_t k = 0; k < common_dim; k++)
            {
                sum += A->data[(i*A->cols)+k] * B->data[j + (k*B->cols)];
            }
            C->data[(i*C->cols) + j] = sum;
        }
    }
    return C;
}

void matrix_print(matrix_t* m)
{
    printf("\n");
    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            printf("%f ", m->data[(i*m->cols)+ j]);
        }
        printf("\n");
    }
}

inline static float sigmoid(float val)
{
    return 1.0/(1.0+expf(-val));
}

/**
 * @brief Apply the sigmoid function element wise
 * 
 * @param m 
 */
void matrix_sigmoid(matrix_t* m)
{
    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            m->data[(i*m->cols) + j] = sigmoid(m->data[(i*m->cols) + j]);
        }
    }
}

int matrix_argmax(const matrix_t* m)
{
    int max = 0;
    float max_val = 0.0;
    for (int i = 0; i < m->rows*m->cols; i++)
    {
        if(m->data[i] > max_val)
        {
            max_val = m->data[i];
            max = i;
        }
    }
    return max;
}

void matrix_destroy(matrix_t* mm)
{
    free(mm->data);
    free(mm);
}