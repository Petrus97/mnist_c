#include "pgm.h"
#include "mnist.h"

#include <stdio.h>
#include <string.h>

static const char *prefix = "./images/";

static uint64_t idx = 0;

void pgm_save_image(uint8_t *image)
{
    FILE *f = NULL;
    char filename[64] = {0};
    sprintf(filename, "%s_%lu.pgm", prefix, idx++);
    f = fopen(filename, "wb");
    if (f == NULL)
    {
        return;
    }
    fprintf(f, "P2\n");
    fprintf(f, "28 28\n"); // FIXME hardcoded for now
    fprintf(f, "255\n");
    for (size_t i = 0; i < IMAGE_DIM; i++)
    {
        fprintf(f, "%u ", image[i]);
        if ((i + 1) % 28 == 0)
        {
            fprintf(f, "\n");
        }
    }
    fclose(f);
}