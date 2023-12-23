#include "pgm.h"
#include "mnist.h"
#include "normal_distribution.h"
#include "nn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


train_data_t train_data = {
    .images = {{{0}}}, // avoid -Wpedantic and -Wmissing-braces
    .labels = {0}
};

test_data_t test_data = {
    .images = {{{0}}},
    .labels = {0}
};

float A_test[3][2] = {
    {3, 1},
    {0, 2},
    {1, 0}
};

float B_test[2][4] = {
    {2, 4, 1, 0},
    {0, 0, 1, 0}
};

int main()
{
    //check_magic_number(TRAIN_IMAGES_PATH);
    //check_dimensions(TRAIN_IMAGES_PATH, IMAGES);
    //display_first_image(TRAIN_IMAGES_PATH);
    // mnist_load_data(&train_data, &test_data);
    // for (size_t i = 0; i < 50; i++)
    // {
    //     pgm_save_image(train_data.images[i].data);
    //     printf("%ld.pgm: %u\n", i, train_data.labels[i]);
    // }
    seed_random();
    // uint16_t layers[3] = {784,30,10};
    // network_t* nn = nn_create(layers, 3);
    // for (size_t i = 0; i < nn->num_layers - 1; i++)
    // {
    //     printf("Biases[%ld]: (%d,%d)\n", i, nn->biases[i]->rows, nn->biases[i]->cols);
    //     printf("Weights[%ld]: (%d,%d)\n", i, nn->weights[i]->rows, nn->weights[i]->cols);
    // }
    
    // nn_destroy(nn);
    
    matrix_t* A = matrix_create(3, 2);
    matrix_t* B = matrix_create(2, 4);
    memcpy(A->data, A_test, A->rows * A->cols * sizeof(float));
    memcpy(B->data, B_test, B->rows * B->cols * sizeof(float));

    matrix_t* C = matrix_dot(A, B);


    matrix_print(A);
    matrix_print(B);
    matrix_print(C);

    matrix_sigmoid(C);
    matrix_print(C);
    printf("Argmax: %d\n", matrix_argmax(C));


    matrix_destroy(A);
    matrix_destroy(B);
    matrix_destroy(C);
    return 0;
}