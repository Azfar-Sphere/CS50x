#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("\n");

    // Starting Size:
    int s;
    do
    {
        s = get_int("Starting Population Size?\n");
    }
    while (s < 9);

    printf("\n");

    // Ending Size:
    int e;
    do
    {
        e = get_int("Ending Population size?\n");
    }
    while (e < s);
    printf("\n");

    // Calculating Years to Reach End Population Size
    int n = 0;
    for (int x = s; x < e; x = ((x / 3) - (x / 4) + x))
    {
        n++;
    }

    // Printing the Number of Years
    printf("Years: %i\n", n);
}
