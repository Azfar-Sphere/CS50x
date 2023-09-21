#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Declares Functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Asks for Text
    string text;
    do
    {
        text = get_string("Please Enter Text (note: no blank spaces at the start or the end):\n");
    }
    while (isblank(text[0]) || isblank(text[strlen(text) - 1]) || count_letters(text) == 0);

    // Calls functions and calcultes Letters, Words and Sentences
    int le = count_letters(text);
    int wo = count_words(text);
    int se = count_sentences(text);

    // Calculates Letters per 100 words and sentence per 100 words
    // Calculates Index
    float l = (((float)le / wo) * 100.0);
    float s = (((float)se / wo) * 100.0);
    float index = ((0.0588 * l) - (0.296 * s) - 15.8);

    // Prints Index if index is 1 to 15, else prints before grade 1 or grade 16+
    if (1 <= index && index < 16)
    {
        printf("Grade %.0f\n", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }

}

// Calculates Letters in the String by counting chars
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Calculates words in the String by counting blank spaces
int count_words(string text)
{
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    return words;
}

// Calculates sentences by counting '.', '?' or '!'
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        switch (text[i])
        {
            case '.':
                sentences++;
                break;

            case '?':
                sentences++;
                break;

            case '!':
                sentences++;
                break;

            default:
                sentences += 0;
                break;
        }
    }
    return sentences;
}