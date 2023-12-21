#include "mnist.h"
#include <stdio.h>

int main()
{
    check_magic_number(TRAIN_IMAGES_PATH);
    check_dimensions(TRAIN_IMAGES_PATH, IMAGES);
    display_first_image(TRAIN_IMAGES_PATH);
    return 0;
}