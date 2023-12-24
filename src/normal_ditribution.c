#include "normal_distribution.h"

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.141592653589793238462643383279502884

static bool need_new = true;
static double z0 = 0.0;
static double z1 = 0.0;

void seed_random(void)
{
    srand(time(NULL));
}

static inline double runif(void)
{
    return ((double)rand()) / ((double)RAND_MAX + 1.0);
}

double rand_norm(void)
{

    if (need_new)
    {
        double u1, u2;
        do
        {
            u1 = runif();
        } while (u1 <= FLT_EPSILON);
        u2 = runif();
        z0 = sqrt(-2.0 * logf(u1)) * cos(2.0 * PI * u2);
        z1 = sqrt(-2.0 * logf(u1)) * sin(2.0 * PI * u2);
        need_new = !need_new;
        return z0;
    }
    else
    {
        need_new = !need_new;
        return z1;
    }
    
}