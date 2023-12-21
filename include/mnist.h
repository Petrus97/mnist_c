#ifndef MNIST_H
#define MNIST_H

#include <stdint.h>

// Training set
#define TRAIN_IMAGES_PATH "./data/train-images-idx3-ubyte"
#define TRAIN_LABELS_PATH "./data/train-labels-idx1-ubyte"
// Test set
#define TEST_IMAGES_PATH "./data/t10k-images-idx3-ubyte"
#define TEST_LABELS_PATH "./data/t10k-labels-idx1-ubyte"

// Magic numbers
#define IMAGES_MAGIC_NUMBER 0x0803
#define LABELS_MAGIC_NUMBER 0x0801

// Set dimensions
#define DIM_TRAIN_SET 60000 // train set dimension
#define DIM_TEST_SET 10000  // test set dimension

// Offsets
#define LABELS_OFFSET 2 * sizeof(uint32_t)
#define IMAGES_OFFSET 4 * sizeof(uint32_t)

#define IMAGE_DIM 784 // 28x28

typedef enum
{
    IMAGES,
    LABELS
} data_type_t;

typedef struct image_t
{
    uint8_t data[IMAGE_DIM];
    // TODO add some padding for cache lines
} image_t;

typedef uint8_t label_t;

typedef struct train_data_t
{
    image_t images[DIM_TRAIN_SET];
    label_t labels[DIM_TRAIN_SET];
} train_data_t;

typedef struct test_data_t
{
    image_t images[DIM_TEST_SET];
    label_t labels[DIM_TEST_SET];
} test_data_t;


void check_magic_number(const char *path);
void check_dimensions(const char *path, data_type_t data);
void display_first_image(const char* path);

void mnist_load_data(train_data_t* train_data, test_data_t* test_data);

#endif