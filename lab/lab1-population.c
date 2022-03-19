#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Prompt for start and end size
    long initialPop, finalPop;
    do
    {
        initialPop = get_int("Initial size (minimum 9): ");
    }
    while (initialPop < 9);
    do
    {
        finalPop = get_int("Final population size (minimum 10): ");
    }
    while (finalPop < initialPop);

    // Calculate number of years
    int time = 0;
    do
    {
        initialPop = round(initialPop + (initialPop / 3) - (initialPop / 4));
        time += 1;
    }
    while (initialPop < finalPop);

    // Print number of years
    printf("Years: %i\n", time);
}