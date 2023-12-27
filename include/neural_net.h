#ifndef NEURAL_NET_H
#define NEURAL_NET_H

/**
 * @file neural_net.h
 * @author Alessio Petruccelli (ale.petru97@gmail.com)
 * @brief Hardcoded version of the neural network to run on the microcontroller.
 * @version 0.1
 * @date 2023-12-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "mnist.h"

#ifndef NUM_LAYERS
#define NUM_LAYERS 3 
#endif

#ifndef INPUT_LAYER
#define INPUT_LAYER 784
#endif

#ifndef HIDDEN_LAYER
#define HIDDEN_LAYER 30
#endif

#ifndef OUTPUT_LAYER
#define OUTPUT_LAYER 10
#endif

typedef double biases_t;
typedef double weights_t;
typedef double activations_t;

typedef struct layer_t
{
    uint16_t num_neurons;
    biases_t** biases;
    weights_t** weights;
    activations_t** activations;
} layer_t;

typedef struct input_layer_t
{
    uint16_t num_neurons;
    activations_t activations[INPUT_LAYER][1];
} input_layer_t;

typedef struct hidden_layer_t
{
    uint16_t num_neurons;
    biases_t biases[HIDDEN_LAYER][1];
    weights_t weights[HIDDEN_LAYER][INPUT_LAYER];
    activations_t activations[HIDDEN_LAYER][1];
} hidden_layer_t;

typedef struct output_layer_t
{
    uint16_t num_neurons;
    biases_t biases[OUTPUT_LAYER][1];
    weights_t weights[OUTPUT_LAYER][HIDDEN_LAYER];
    activations_t activations[OUTPUT_LAYER][1];
} output_layer_t;

typedef struct neural_net_t
{
    uint8_t num_layers;
    // layer_t sizes[NUM_LAYERS];
    input_layer_t input_layer;
    hidden_layer_t hidden_layer;
    output_layer_t output_layer;
} neural_net_t;

void neural_net_init(neural_net_t *net);
int neural_net_evaluate(neural_net_t *net, const test_data_t *test_data);

#endif