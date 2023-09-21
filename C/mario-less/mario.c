#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    //Gets height of Pyramid
    do
    {
        height = get_int("what is the height of the pyramid?\n");
    }
    while (height < 1 || height > 8);

    // Prints Pyramid
    for (int x = 1; x <= height; x++)
    {
        // Prints Blanks
        for (int z = 1; z <= (height - x); z++)
        {
            printf(" ");
        }

        // Prints Hashes
        for (int y = 1; y <= x; y++)
        {
            printf("#");
        }

        printf("\n");
    }
}