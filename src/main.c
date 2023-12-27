#include "pgm.h"
#include "mnist.h"
#include "normal_distribution.h"
// #include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "biases.h"
//#include "weights.h"
#include "neural_net.h"


train_data_t train_data = {
    .images = {{{0}}}, // avoid -Wpedantic and -Wmissing-braces
    .labels = {0}
};

test_data_t test_data = {
    .images = {{{0}}},
    .labels = {0}
};

double A_test[3][2] = {
    {3, 1},
    {0, 2},
    {1, 0}
};

double B_test[2][4] = {
    {2, 4, 1, 0},
    {0, 0, 1, 0}
};

neural_net_t nn;

int main()
{
    //check_magic_number(TRAIN_IMAGES_PATH);
    //check_dimensions(TRAIN_IMAGES_PATH, IMAGES);
    //display_first_image(TRAIN_IMAGES_PATH);
    mnist_load_data(&train_data, &test_data);
    for (size_t i = 0; i < 50; i++)
    {
        // pgm_save_image(test_data.images[i].data);
        printf("%ld.pgm: %u\n", i, test_data.labels[i]);
    }
    seed_random();
    // uint16_t layers[3] = {784,30,10};
    neural_net_init(&nn);
    neural_net_evaluate(&nn, &test_data);
    // network_t* nn = nn_create(layers, 3);
    // for (size_t i = 0; i < nn->num_layers - 1; i++)
    // {
    //     printf("Biases[%ld]: (%d,%d)\n", i, nn->biases[i]->rows, nn->biases[i]->cols);
    //     printf("Weights[%ld]: (%d,%d)\n", i, nn->weights[i]->rows, nn->weights[i]->cols);
    // }
    // memcpy(nn->biases[0]->data, b0, nn->biases[0]->rows * nn->biases[0]->cols * sizeof(double));
    // memcpy(nn->biases[1]->data, b1, nn->biases[1]->rows * nn->biases[1]->cols * sizeof(double));
    // memcpy(nn->weights[0]->data, w0, nn->weights[0]->rows * nn->weights[0]->cols * sizeof(double));
    // memcpy(nn->weights[1]->data, w1, nn->weights[1]->rows * nn->weights[1]->cols * sizeof(double));
    
    // int ret = nn_evaluate(nn, &test_data);
    // printf("Evaluation: %d - %d\n", ret, DIM_TEST_SET);
    // nn_destroy(nn);

    return 0;
}