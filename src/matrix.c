#include "matrix.h"
#include <stdlib.h>

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

void matrix_destroy(matrix_t* mm)
{
    free(mm->data);
    free(mm);
}