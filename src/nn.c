#include "nn.h"
#include "normal_distribution.h"
#include "utlis.h"

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
network_t *nn_create(uint16_t *sizes, uint8_t sizes_len)
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
        nn->sizes = (uint16_t *)calloc(sizes_len, sizeof(uint16_t));
        memcpy(nn->sizes, sizes, 3 * sizeof(uint16_t));
        // Allocate biases matrixes
        nn->biases = (biases_t **)calloc(nn->num_layers - 1, sizeof(biases_t *)); // pointer to biases arrays
        // Compute/Initialize biases according to normal distribution
        for (size_t i = 1; i < nn->num_layers; i++) // not the input layer
        {
            // Create bias i-1 matrix
            nn->biases[i - 1] = matrix_create(nn->sizes[i], 1);
            for (size_t j = 0; j < nn->biases[i - 1]->rows; j++)
            {
                for (size_t k = 0; k < nn->biases[i - 1]->cols; k++)
                {
                    nn->biases[i - 1]->data[(j * nn->biases[i - 1]->cols) + k] = rand_norm();
                }
            }
        }
        // Allocate weights matrixes
        nn->weights = (weights_t **)calloc(nn->num_layers - 1, sizeof(weights_t *)); // pointer to weights arrays
        // Compute/Initialize weights according to normal distribution
        for (size_t i = 1; i < nn->num_layers; i++) // not the input layer
        {
            // Create weight i-1 matrix
            // dimension of the array = layer_size x prev_layer
            nn->weights[i - 1] = matrix_create(nn->sizes[i], nn->sizes[i - 1]);
            // i.e. array of 30x784
            for (size_t j = 0; j < nn->weights[i - 1]->rows; j++)
            {
                for (size_t k = 0; k < nn->weights[i - 1]->cols; k++)
                {
                    nn->weights[i - 1]->data[(j * nn->weights[i - 1]->cols) + k] = rand_norm();
                }
            }
        }
        return nn;
    }
}

matrix_t *nn_feedforward_r(network_t *nn, matrix_t *input, int layer_num)
{
    if(layer_num == nn->num_layers - 1)
    {
        return input; // TODO
    }
    else
    {
        matrix_t* new_input = matrix_calc_activation(input, nn->weights[layer_num], nn->biases[layer_num]);
        matrix_destroy(input);
        return nn_feedforward_r(nn, new_input, ++layer_num);
    }

}


matrix_t *nn_feedforward(network_t *nn, matrix_t *input)
{
    return nn_feedforward_r(nn, input, 0);
}

int nn_evaluate(network_t *nn, const test_data_t *test_data)
{
    int sum = 0;

    for (size_t i = 0; i < BUFFER_SIZE(test_data->labels); i++)
    {
        matrix_t *input = matrix_create(IMAGE_DIM, 1); // OBS! Deallocation of this matrix inside the feedforward!
        matrix_t *result = nn_feedforward(nn, input);
        // // matrix_print(result);
        int x = matrix_argmax(result);
        // printf("%d - %d\n", x, test_data->labels[i]);
        sum += (x == test_data->labels[i]);
        // matrix_destroy(input);
        matrix_destroy(result);
    }
    return sum;
}

void nn_destroy(network_t *nn)
{
    if (nn != NULL)
    {
        for (size_t i = 0; i < nn->num_layers - 1; i++)
        {
            matrix_destroy(nn->biases[i]);
            matrix_destroy(nn->weights[i]);
        }
        free(nn->biases);
        free(nn->weights);
        free(nn->sizes);

        free(nn);
    }
}