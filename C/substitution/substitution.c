#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
char *cipher(char *plaintext, char *key);
bool check(char *argv);

int main(int argc, char *argv[])
{
    // Checks if there are 2 command line arguments
    if (argc != 2 || check(argv[1]))
    {
        printf("Error! Usage: ./subsitution key\n");
        return 1;
    }

    // Gets the Key
    char *key = argv[1];

    // Gets plaintext
    char *plaintext = get_string("plaintext: ");

    // Converts plaintext to ciphertext then prints
    char *ciphertext = cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    // Frees allocated memory
    free(ciphertext);
    return 0;
}

// Cipher Function
char *cipher(char *plaintext, char *key)
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
            // Calculates index of each letter and then replaces it
            if (isupper(plaintext[i]))
            {
                int index = plaintext[i] - 'A';
                if (index >= 0 && index < 26)
                {
                    ciphertext[i] = toupper(key[index]);
                }
            }

            if (islower(plaintext[i]))
            {
                int index = plaintext[i] - 'a';
                if (index >= 0 && index < 26)
                {
                    ciphertext[i] = tolower(key[index]);
                }
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Replaces last char with NUL
    ciphertext[n] = '\0';
    return ciphertext;
}

// Checks if key is numerical or not
bool check(char *argv)
{
    int n = strlen(argv);
    int nsum = 0;

    // Checks for 26 Letters
    if (n != 26)
    {
        printf("Enter 26 letters for the key!\n");
        return true;
    }

    for (int i = 0; i < n; i++)
    {
        // Checks if there are any digits
        if (isdigit(argv[i]))
        {
            return true;
        }

        // Checks for duplication
        for (int j = i + 1; j < n; j++)
        {
            if (tolower(argv[i]) == tolower(argv[j]))
            {
                return true;
            }
        }

        nsum += tolower(argv[i]);
    }

    // Checks if there are all letter of the alphabet
    if (nsum != 2847)
    {
        printf("Enter All 26 Letters!\n");
        return true;
    }

    return false;
}