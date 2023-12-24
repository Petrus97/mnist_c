#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H


void seed_random(void);

/**
 * @brief Generate random number from normal distribution N~(0,1)
 * Using the Box-Muller transform
 */
double rand_norm(void);

#endif