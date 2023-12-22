#include "nn.h"
#include "normal_distribution.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a Neural Network
 * The construction of this network follows the example (784, 30, 10) where
 * 784 input layer
 * 30 hidden layer
 * 10 output layer
 *
 * @param sizes array which contains the sizes i.e. uint8_t arr[3] = {784,30,10};
 * @param sizes_len the size of the array, in the example 3
 * @return network_t*
 */
network_t *nn_create(uint8_t *sizes, uint8_t sizes_len)
{
    network_t *nn = NULL;
    if (sizes_len == 1)
    {
        printf("Only input layer!\n");
        return NULL;
    }
    else if (sizes_len == 2)
    {
        printf("Only input and output layers!\n");
        return NULL;
    }
    else
    {
        nn = (network_t *)calloc(1, sizeof(network_t));
        nn->num_layers = sizes_len;
        // init sizes array
        nn->sizes = (uint8_t *)calloc(sizes_len, sizeof(uint8_t));
        memcpy(nn->sizes, sizes, sizes_len);
        // Allocate biases
        nn->biases = (biases_t **)calloc(nn->num_layers - 1, sizeof(biases_t *)); // pointer to biases arrays
        // Compute/Initialize biases according to normal distribution
        for (size_t i = 1; i < nn->num_layers; i++) // not the input layer
        {
            nn->biases[i - 1] = (biases_t *)calloc(nn->sizes[i], sizeof(biases_t)); //
            for (size_t j = 0; j < nn->sizes[i]; j++)
            {
                nn->biases[i - 1][j] = rand_norm();
            }
        }
        // Allocate weights
        nn->weights = (weights_t **)calloc(nn->num_layers - 1, sizeof(weights_t *)); // pointer to weights arrays
        // Compute/Initialize weights according to normal distribution
        for (size_t i = 1; i < nn->num_layers; i++) // not the input layer
        {
            // dimension of the array = layer_size x prev_layer
            // i.e. array of 30x784
            int n_weights = nn->sizes[i] * nn->sizes[i - 1];
            nn->weights[i - 1] = (weights_t *)calloc(n_weights, sizeof(weights_t)); 
            for (size_t j = 0; j < n_weights; j++)
            {
                nn->weights[i - 1][j] = rand_norm();
            }
        }
        return nn;
    }
}

void nn_destroy(network_t *nn)
{
    if (nn != NULL)
    {
        for (size_t i = 0; i < nn->num_layers - 1; i++)
        {
            free(nn->biases[i]);
            free(nn->weights[i]);
        }
        free(nn->biases);
        free(nn->weights);
        free(nn->sizes);
        
        free(nn); 
    }
}