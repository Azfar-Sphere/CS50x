#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int len = strlen(input) - 1;
    int intv = 0;
    intv = *input - '0';
    intv *= pow(10, len);

    if (*(input + 1) != '\0')
    {

        intv += convert(input + 1);
    }

    return intv;
}