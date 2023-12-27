#include "neural_net.h"
#include "biases.h"
#include "utlis.h"
#include "weights.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void neural_net_init(neural_net_t *net)
{
    net->num_layers = NUM_LAYERS;
    // Init input layer
    net->input_layer.num_neurons = INPUT_LAYER;
    // net->input_layer.activations = ; // FIXME add the image

    // Init the hidden layer
    net->hidden_layer.num_neurons = HIDDEN_LAYER;
    memcpy(net->hidden_layer.biases, b0, MATRIX_SIZE(b0) * sizeof(double));
    memcpy(net->hidden_layer.weights, w0, MATRIX_SIZE(w0) * sizeof(double));
    memset(net->hidden_layer.activations, 0, MATRIX_SIZE(net->hidden_layer.activations) * sizeof(double));

    // Init the output layer
    net->output_layer.num_neurons = OUTPUT_LAYER;
    memcpy(net->output_layer.biases, b1, MATRIX_SIZE(b1) * sizeof(double));
    memcpy(net->output_layer.weights, w1, MATRIX_SIZE(w1) * sizeof(double));
    memset(net->output_layer.activations, 0, MATRIX_SIZE(net->output_layer.activations) * sizeof(double));
}

inline static double sigmoid(double val)
{
    return 1.0 / (1.0 + exp(-val));
}

static void neural_net_calc_activation(neural_net_t *net)
{
    // FIXME for now let's do it here
    /** input - hidden layer
     * dot(w, a) + b
     * dim(w) = [30][784]
     * dim(a) = [784][1]
     * dim(b) = [30][1]
     */
    for (size_t i = 0; i < NUM_ROWS(net->hidden_layer.weights); i++)
    {
        for (size_t j = 0; j < NUM_COLS(net->input_layer.activations); j++)
        {
            for (size_t k = 0; k < net->input_layer.num_neurons; k++)
            {
                net->hidden_layer.activations[i][j] +=
                    net->hidden_layer.weights[i][k] * net->input_layer.activations[k][j];
            }
        }
    }
    // sum the bias and calc sigmoid
    for (size_t i = 0; i < NUM_ROWS(net->hidden_layer.biases); i++)
    {
        net->hidden_layer.activations[i][0] += net->hidden_layer.biases[i][0];
    }
    for (size_t i = 0; i < NUM_ROWS(net->hidden_layer.biases); i++)
    {
        net->hidden_layer.activations[i][0] = sigmoid(net->hidden_layer.activations[i][0]);
    }

    /** hidden - output layer
     * dot(w, a) + b
     * dim(w) = [10][30]
     * dim(a) = [30][1]
     * dim(b) = [10][1]
     */
    for (size_t i = 0; i < NUM_ROWS(net->output_layer.weights); i++)
    {
        for (size_t j = 0; j < NUM_COLS(net->hidden_layer.activations); j++)
        {
            for (size_t k = 0; k < net->hidden_layer.num_neurons; k++)
            {
                net->output_layer.activations[i][j] +=
                    net->output_layer.weights[i][k] * net->hidden_layer.activations[k][j];
            }
        }
    }
    // sum the bias and sigmoid
    for (size_t i = 0; i < NUM_ROWS(net->output_layer.biases); i++)
    {
        net->output_layer.activations[i][0] += net->output_layer.biases[i][0];
    }
    for (size_t i = 0; i < NUM_ROWS(net->output_layer.biases); i++)
    {
        net->output_layer.activations[i][0] = sigmoid(net->output_layer.activations[i][0]);
    }
    return;
}

static int argmax(const output_layer_t *out)
{
    int max = 0;
    double max_val = 0.0;
    for (int i = 0; i < NUM_ROWS(out->activations); i++)
    {
        if (out->activations[i][0] > max_val)
        {
            max_val = out->activations[i][0];
            max = i;
        }
    }
    return max;
}

static void reset_layers(neural_net_t *net)
{
    memset(net->hidden_layer.activations, 0, MATRIX_SIZE(net->hidden_layer.activations) * sizeof(double));
    memset(net->output_layer.activations, 0, MATRIX_SIZE(net->hidden_layer.activations) * sizeof(double));
}

int neural_net_evaluate(neural_net_t *net, const test_data_t *test_data)
{
    int sum = 0;

    for (size_t i = 0; i < BUFFER_SIZE(test_data->labels); i++)
    {
        // matrix_t *input = matrix_create(IMAGE_DIM, 1); // OBS! Deallocation of this matrix inside the feedforward!
        // Fill the input layer with the image
        for (size_t ii = 0; ii < net->input_layer.num_neurons; ii++)
        {
            net->input_layer.activations[ii][0] = (double)test_data->images[i].data[ii] / 256.0; // NOTE: the values in python training are scaled
        }
        // Feedforward
        neural_net_calc_activation(net);
        // Evaluate output
        int x = argmax(&(net)->output_layer);

        sum += (x == test_data->labels[i]);
        reset_layers(net);
    }
    printf("%d / %ld\n", sum, BUFFER_SIZE(test_data->labels));
    return sum;
}