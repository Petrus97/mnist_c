#include "normal_distribution.h"

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.141592653589793238462643383279502884

static bool need_new = true;
static float z0 = 0.0;
static float z1 = 0.0;

void seed_random(void)
{
    srand(time(NULL));
}

static inline float runif(void)
{
    return ((float)rand()) / ((float)RAND_MAX + 1.0);
}

float rand_norm(void)
{

    if (need_new)
    {
        float u1, u2;
        do
        {
            u1 = runif();
        } while (u1 <= FLT_EPSILON);
        u2 = runif();
        z0 = sqrtf(-2.0 * logf(u1)) * cosf(2.0 * PI * u2);
        z1 = sqrtf(-2.0 * logf(u1)) * sinf(2.0 * PI * u2);
        need_new = !need_new;
        return z0;
    }
    else
    {
        need_new = !need_new;
        return z1;
    }
    
}