#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Prints the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Computes and return score for string
    int score = 0;
    for (int i = 0, x = strlen(word); i < x; i++)
    {
        // Checks for uppercase
        if (isupper(word[i]))
        {
            int n = (int) word[i];
            score += POINTS[(n - 65)];
        }

        // Checks for lowercase
        else if (islower(word[i]))
        {
            int n = (int) word[i];
            score += POINTS[(n - 97)];
        }

        // If not an alphabet then adds 0 to score
        else
        {
            score += 0;
        }
    }
    return score;
}

