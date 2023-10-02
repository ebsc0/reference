#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Generate random int from lower to upper [lower, upper)
 * 
 * @param lower 
 * @param upper 
 * @return int 
 */
int rand_int(int lower, int upper)
{
    return (rand() % (upper - lower)) + lower;
}