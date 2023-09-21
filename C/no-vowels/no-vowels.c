#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Uses 'string.h' header

void no_vowel(string word);

int main(int argc, string argv[])
{
    // Checks if there is a word
    if (argc != 2)
    {
        printf("Error, Please input one word\n");
        return 1;
    }

    // If there is a word, carries on function
    else
    {
        no_vowel(argv[1]);
    }

}

// Function to Replace Vowels
void no_vowel(string word)
{
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        // Checks each Letter
        switch (word[i])
        {
            case 'a':
                printf("6");
                break;

            case 'e':
                printf("3");
                break;

            case 'i':
                printf("1");
                break;

            case 'o':
                printf("0");
                break;

            // Print non-vowels
            default:
                printf("%c", word[i]);
        }
    }
    printf("\n");
}

