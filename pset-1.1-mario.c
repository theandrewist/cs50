#include <stdio.h>
#include <cs50.h>

void build(int height);
int main(void)                                    // Constrain input values
{
    int height;
    do
    {
        height = get_int("Enter a number between 1 and 8: ");       // Question
    }
    while (height < 1 || height > 8);             // Reject values which are not between 0 and 8

    if (1 <= height && height <= 8)               // Accept values and build triangle
    {
        build(height);
    }
}

void build(int height)                            // Build triangle function with respect to height
{
    for (int row = 1; row <= height; row++)       // For each row
    {
        for (int j = 1; j <= height - row; j++)   // Place (height - row) number of spaces
        {
            printf(" ");
        }
        for (int j = 1; j <= row; j++)            // Place (row) number of hashes
        {
            printf("#");
        }
        printf("  ");                             // Print (2) spaces
        for (int j = 1; j <= row; j++)            // Place (row) number of hashes again
        {
            printf("#");
        }
        printf("\n");                             // New line
    }
}