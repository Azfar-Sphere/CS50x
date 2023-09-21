#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

char *check(long number);

int main(void)
{
    // Gets the Card Number
    long ccno;
    ccno = get_long("Credit Card No:\n");

    // Prints if Card is Valid or Not
    printf("%s\n", check(ccno));
}

char *check(long number)
{
    // Calculates the Number of Card Digits and stores each Digit in an array
    int digits = 0;
    int num_index[16];
    while (number != 0)
    {
        num_index[digits] = number % 10;
        digits++;
        number /= 10;
    }

    // returns invalid if Number of Card Digits not Equal to 13, 15 or 16
    if (digits != 13 && digits != 15 && digits != 16)
    {
        return "INVALID";
    }

    // Uses Luhn's algorithm to calculate if card is Valid or Not
    int sum = 0;

    // Multiples every Other digit from Second last Digit by 2, add individual digits
    for (int i = 0, j = 1; i <= digits / 2; i++, j += 2)
    {
        int sum_a = num_index[j] * 2;
        while (sum_a != 0)
        {
            sum += sum_a % 10;
            sum_a /= 10;
        }
    }

    // Adds all the numbers not multipled by 2
    for (int i = 0, j = 0; i <= digits / 2; i++, j += 2)
    {
        sum += num_index[j];
    }

    // Checks Modulo of no, if not divisble by 10, returns invalid
    if ((sum % 10) != 0)
    {
        return "INVALID";
    }

    // Checks the First and Second Digit of Cards, return appropriate card maker
    switch (num_index[digits - 1])
    {
        case 4:
            return "VISA";
            break;

        case 5:
            switch (num_index[digits - 2])
            {
                case 1:
                    return "MASTERCARD";
                    break;

                case 2:
                    return "MASTERCARD";
                    break;

                case 3:
                    return "MASTERCARD";
                    break;

                case 4:
                    return "MASTERCARD";
                    break;

                case 5:
                    return "MASTERCARD";
                    break;

                default:
                    return "INVALID";
                    break;
            }

        case 3:
            switch (num_index[digits - 2])
            {
                case 4:
                    return "AMEX";
                    break;

                case 7:
                    return "AMEX";
                    break;

                default:
                    return "INVALID";
            }

        default:
            return "INVALID";
            break;
    }

    return "INVALID";
}