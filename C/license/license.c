#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char *buffer = malloc(7);
    if (buffer == NULL)
    {
        printf("Memory Allocation Error!");
        return 2;
    }

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    // Stop the Programme if File is not Found
    if (infile == NULL)
    {
        printf("Invalid File!");
        return 1;
    }

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        plates[idx] = buffer;
        idx++;

        // Allocates new Memory to Buffer
        buffer = (char *) malloc(7);

        // Checks if Memory Available
        if (buffer == NULL)
        {
            printf("Memory Allocation Error!");
            return 2;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }
    free(buffer);
    fclose(infile);
    return 0;
}
