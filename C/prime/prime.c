#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

// Function to Check if a number is prime or not
bool prime(int number)
{
    for (int x = 2; x < number; x++)
    {
        float remainder = (number % x);
        if (remainder == 0 || number == 1)
        {
            return false;
        }
    }
    return true;
}
