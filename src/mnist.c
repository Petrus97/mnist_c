#include "mnist.h"
#include "utlis.h"
#include <stdio.h>

void check_magic_number(const char *path)
{
    FILE *file = NULL;
    file = fopen(path, "rb");
    if (file == NULL)
    {
        printf("Error opening file %s\n", path);
        return;
    }
    uint32_t magic = 0;
    if (fread(&magic, sizeof(uint32_t), 1, file))
    {
        magic = swap_endianess_32(magic);
        if (magic == IMAGES_MAGIC_NUMBER || magic == LABELS_MAGIC_NUMBER)
        {
            printf("Magic: 0x%04X\n", magic);
        }
        else
        {
            printf("Not valid magic number! Got: 0x%04X\n", magic);
            goto cleanup;
        }
    }
cleanup:
    fclose(file);
    return;
}

void check_dimensions(const char *path, data_type_t data)
{
    FILE *file = NULL;
    file = fopen(path, "rb");
    if (file == NULL)
    {
        return;
    }
    fseek(file, sizeof(uint32_t), SEEK_SET); // skip magic number
    switch (data)
    {
    case IMAGES: {
        uint32_t metadata[3] = {0}; // n_images, n_rows, n_cols
        if (fread(metadata, sizeof(uint32_t), BUFFER_SIZE(metadata), file))
        {
            uint32_t n_images = swap_endianess_32(metadata[0]);
            uint32_t n_rows = swap_endianess_32(metadata[1]);
            uint32_t n_cols = swap_endianess_32(metadata[2]);
            if (n_images == DIM_TRAIN_SET || n_images == DIM_TEST_SET)
            {
                printf("Set of %u images\n", n_images);
            }
            else
            {
                printf("Expected 60k or 10k - got %u", n_images);
                goto cleanup;
            }
            if ((n_cols * n_rows) == IMAGE_DIM)
            {
                printf("Images dimensions: %ux%u\n", n_rows, n_cols);
            }
            else
            {
                printf("Expected %u - got %ux%u\n", IMAGE_DIM, n_rows, n_cols);
                goto cleanup;
            }
        }
        break;
    }
    case LABELS: {
        uint32_t n_items = 0; // n_images, n_rows, n_cols
        if (fread(&n_items, sizeof(uint32_t), 1, file))
        {
            n_items = swap_endianess_32(n_items);
            if (n_items == DIM_TRAIN_SET || n_items == DIM_TEST_SET)
            {
                printf("Set of: %u labels\n", n_items);
            }
            else
            {
                printf("Expected 60k or 10k - got %u", n_items);
                goto cleanup;
            }
        }
        break;
    }
    default:
        break;
    }
cleanup:
    if (file != NULL)
        fclose(file);
}

void display_first_image(const char *path)
{
    FILE *file = NULL;
    file = fopen(path, "rb");
    if (file == NULL)
    {
        return;
    }
    fseek(file, IMAGES_OFFSET, SEEK_SET);
    uint8_t image[IMAGE_DIM];
    if (fread(image, sizeof(uint8_t), IMAGE_DIM, file))
    {
        for (size_t i = 0; i < 28; i++)
        {
            for (size_t j = 0; j < 28; j++)
            {
                printf("%u ", image[(i * 28) + j]);
            }
            printf("\n");
        }
    }
    {
        FILE *new = NULL;
        new = fopen("data0.pgm", "wb");
        fprintf(new, "P2\n");
        fprintf(new, "28 28\n");
        fprintf(new, "255\n");
        for (size_t i = 0; i < IMAGE_DIM; i++)
        {
            fprintf(new, "%u ", image[i]);
            if ((i + 1) % 28 == 0)
            {
                fprintf(new, "\n");
            }
        }
        fclose(new);
    }
    fclose(file);
}

static void mnist_load_train_images(train_data_t *train_data)
{
    FILE *f = NULL;
    f = fopen(TRAIN_IMAGES_PATH, "rb");
    if (f == NULL)
    {
        return;
    }
    fseek(f, IMAGES_OFFSET, SEEK_SET); // skip metadata
    for (size_t i = 0; i < DIM_TRAIN_SET; i++)
    {
        if (fread(train_data->images[i].data, sizeof(uint8_t), IMAGE_DIM, f) == 784)
        {
        }
        else
        {
            printf("Error loading image #%ld\n", i);
        }
    }
    fclose(f);
}

static void mnist_load_train_labels(train_data_t *train_data)
{
    FILE *f = NULL;
    f = fopen(TRAIN_LABELS_PATH, "rb");
    if (f == NULL)
    {
        return;
    }
    fseek(f, LABELS_OFFSET, SEEK_SET); // skip metadata
    for (size_t i = 0; i < DIM_TRAIN_SET; i++)
    {
        if (fread(&(train_data)->labels[i], sizeof(uint8_t), 1, f) == 1)
        {
            // printf("%u\n", tmp);
        }
        else
        {
            printf("Error loading label #%ld\n", i);
        }
    }
    fclose(f);
}

static void mnist_load_test_images(test_data_t *test_data)
{
    FILE *f = NULL;
    f = fopen(TEST_IMAGES_PATH, "rb");
    if (f == NULL)
    {
        return;
    }
    fseek(f, IMAGES_OFFSET, SEEK_SET); // skip metadata
    for (size_t i = 0; i < DIM_TEST_SET; i++)
    {
        if (fread(test_data->images[i].data, sizeof(uint8_t), IMAGE_DIM, f) == 784)
        {
        }
        else
        {
            printf("Error loading image #%ld\n", i);
        }
    }
    fclose(f);
}

static void mnist_load_test_labels(test_data_t *test_data)
{
    FILE *f = NULL;
    f = fopen(TEST_LABELS_PATH, "rb");
    if (f == NULL)
    {
        return;
    }
    fseek(f, LABELS_OFFSET, SEEK_SET); // skip metadata
    for (size_t i = 0; i < DIM_TEST_SET; i++)
    {
        if (fread(&(test_data->labels[i]), sizeof(uint8_t), 1, f) == 1)
        {
        }
        else
        {
            printf("Error loading label #%ld\n", i);
        }
    }
    fclose(f);
}

void mnist_load_data(train_data_t *train_data, test_data_t *test_data)
{
    // Load training data
    mnist_load_train_images(train_data);
    mnist_load_train_labels(train_data);
    // Load test data
    mnist_load_test_images(test_data);
    mnist_load_test_labels(test_data);

}

/**
 * @brief Return the Input layer as matrix_t
 * 
 * @param test_data 
 * @return matrix_t* 
 */
matrix_t* mnist_img2matrix(const uint8_t* image)
{
    matrix_t* m = matrix_create(IMAGE_DIM, 1);
    for (size_t i = 0; i < IMAGE_DIM; i++)
    {
        m->data[i] = (float)image[i];
    }
    return m;
}