#ifndef NN_H
#define NN_H

#include <stdint.h>

typedef float biases_t;
typedef float weights_t;


typedef struct metadata_t
{
    int index; // index of the array
    int n_rows; // how many rows has the vector
    int n_cols; // how many cols has the vector
} metadata_t;

typedef metadata_t bias_meta_t;
typedef metadata_t weight_meta_t;


typedef struct network_t
{
    uint8_t num_layers;
    uint16_t* sizes;
    uint8_t metadata_size; // how many biases/weigths arrays I have
    bias_meta_t* b_meta;
    weight_meta_t* w_meta;
    biases_t** biases; // can contain multiple arrays
    weights_t** weights;
} network_t;

network_t* nn_create(uint16_t* sizes, uint8_t sizes_len);

void nn_destroy(network_t* nn);


#endif