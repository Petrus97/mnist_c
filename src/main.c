#include "pgm.h"
#include "mnist.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //check_magic_number(TRAIN_IMAGES_PATH);
    //check_dimensions(TRAIN_IMAGES_PATH, IMAGES);
    //display_first_image(TRAIN_IMAGES_PATH);
    train_data_t* train_data = (train_data_t*)malloc(sizeof(train_data_t));
    test_data_t* test_data = (test_data_t*)malloc(sizeof(test_data_t));
    mnist_load_data(train_data, test_data);
    for (size_t i = 0; i < 50; i++)
    {
        pgm_save_image(train_data->images[i].data);
    }
    
    return 0;
}