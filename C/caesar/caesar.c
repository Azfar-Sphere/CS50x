#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
char *cipher(char *plaintext, int key);
bool check(char *argv);

int main(int argc, char *argv[])
{
    // Checks if there are 2 command line arguments
    if (argc != 2 || check(argv[1]))
    {
        printf("Error! Usage: ./caesar key\n");
        return 1;
    }

    // Converts key from string to int
    int key = atoi(argv[1]);

    // Gets plaintext
    char *plaintext = get_string("plaintext: ");

    // Converts plaintext to ciphertext then prints
    char *ciphertext = cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    // Frees allocated memory
    free(ciphertext);
}

// Cipher Function
char *cipher(char *plaintext, int key)
{
    // Finds length of plaintext
    int n = strlen(plaintext);

    // Allocates memory to ciphertext
    char *ciphertext = malloc((n + 1) * sizeof(char));
    // Checks for memory Error
    if (ciphertext == NULL)
    {
        return "Malloc Failure!";
    }

    // Iterates over each text and ciphers it
    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char c;
            if (isupper(plaintext[i]))
            {
                c = 'A' + (((plaintext[i] + key) - 'A') % 26);
            }

            if (islower(plaintext[i]))
            {
                c = 'a' + (((plaintext[i] + key) - 'a') % 26);
            }

            ciphertext[i] = c;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[n] = '\0';
    return ciphertext;
}

// Checks if key is numerical or not
bool check(char *argv)
{
    int n = strlen(argv);
    for (int i = 0; i < n; i++)
    {
        if (isalpha(argv[i]))
        {
            return true;
        }
    }
    return false;
}