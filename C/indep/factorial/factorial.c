#include <stdio.h>
#include <stdlib.h>

int factorial(int n);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error, please enter a number\n");
        return 1;
    }
    else
    {
        int n = atoi(argv[1]);
        printf("Factorial of %s is: %i\n", argv[1], factorial(n));
    }
}

int factorial(int n)
{
    if (n  == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n-1);
    }
}