#ifndef NN_H
#define NN_H

#include <stdint.h>
#include "matrix.h"

typedef matrix_t biases_t;
typedef matrix_t weights_t;

typedef struct network_t
{
    uint8_t num_layers;
    uint16_t* sizes;
    biases_t** biases; // contains matrixes
    weights_t** weights;
} network_t;

network_t* nn_create(uint16_t* sizes, uint8_t sizes_len);

void nn_destroy(network_t* nn);


#endif