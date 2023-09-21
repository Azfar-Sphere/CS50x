#include <cs50.h>
#include <stdio.h>

void pyramid(int height);

int main(void)
{
    // Gets the height between 1 and 8
    int height;
    do
    {
        height = get_int("What is the height (Between 1 and 8)?\n");
    }
    while (height < 1 || height > 8);

    pyramid(height);
}

void pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        // Prints blank spoces to right align pyramid
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // Prints right pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // Prints Blank between the two pyramids
        printf("  ");
        // Prints left pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // Prints new line
        printf("\n");
    }
}
