#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void string_to_binary(string text);

int main(void)
{
    // Asks for Message, calls for another function
    string text = get_string("Write a message!\n");
    string_to_binary(text);
}

// Function to Print Bulbs
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
    else if (bit == BITS_IN_BYTE)
    {
        printf("\n");
    }
}

void string_to_binary(string text)
{
    // Creates an array which stores decimal values of each character
    int w = strlen(text);
    int decimal_array[w - 1];
    for (int i = 0; i < w; i++)
    {
        decimal_array[i] = (int)text[i];
    }

    // Converts Decimal to Binary
    int binary[w][BITS_IN_BYTE];

    for (int i = 0; i < w; i++)
    {
        // Divides Integer value with powers of 2 from exponent 7 till 0
        for (int f = 7, bit = 0; f >= 0 && bit < 8; f--, bit++)
        {
            // If the Quotient is less than 0, then binary 0
            if (((float)decimal_array[i] / pow(2.0, f)) < 1)
            {
                binary[i][bit] = 0;
            }
            // If Quotient is equal to or more than 1, then binary 1
            else if ((float)(decimal_array[i] / pow(2.0, f)) >= 1)
            {
                binary[i][bit] = 1;
                decimal_array[i] -= pow(2.0, f);
            }
            // Prints Bulbs
            print_bulb(binary[i][bit]);
        }
        // Prints Space After each Byte
        print_bulb(BITS_IN_BYTE);
    }
}