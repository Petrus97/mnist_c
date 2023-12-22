#ifndef NN_H
#define NN_H

#include <stdint.h>

typedef float biases_t;
typedef float weights_t;


typedef struct network_t
{
    uint8_t num_layers;
    uint8_t* sizes;
    biases_t** biases; // can contain multiple arrays
    weights_t** weights;
} network_t;

network_t* nn_create(uint8_t* sizes, uint8_t sizes_len);

void nn_destroy(network_t* nn);


#endif