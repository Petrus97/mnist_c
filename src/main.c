#include "pgm.h"
#include "mnist.h"
#include "normal_distribution.h"
#include <stdio.h>
#include <stdlib.h>


train_data_t train_data = {
    .images = {{{0}}}, // avoid -Wpedantic and -Wmissing-braces
    .labels = {0}
};

test_data_t test_data = {
    .images = {{{0}}},
    .labels = {0}
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
    for (size_t i = 0; i < 15; i++)
    {
        printf("%f\n", rand_norm());
    }
    
    

    return 0;
}