#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int block = 512;

int main(int argc, char *argv[])
{
    // Ensures correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover filename.raw\n");
        return 1;
    }

    // Opens file
    FILE *infile = fopen(argv[1], "r");
    // Checks if File is properly opened
    if (infile == NULL)
    {
        printf("Unable to open File!\n");
        fclose(infile);
        return 1;
    }

    // Creates Buffer
    BYTE *buffer = malloc(block);
    // Checks if Memory is allocated to buffer
    if (buffer == NULL)
    {
        printf("Memory Allocation Error!\n");
        fclose(infile);
        free(buffer);
        return 1;
    }

    int i = 0;
    FILE *img = NULL;
    // Reads through infile and checks for JPEG
    while (fread(buffer, 1, block, infile) == block)
    {
        // Checks beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Closes previous file
            if (img != NULL)
            {
                fclose(img);
            }

            // Creates a new filename
            char *filename = malloc(sizeof(int) * 3);
            if (filename == NULL)
            {
                printf("Memory Allocation Error!\n");
                free(filename);
                free(buffer);
                fclose(img);
                fclose(infile);
                return 1;
            }
            sprintf(filename, "%03i.jpg", i);

            // Opens new file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Unable to open img File!\n");
                free(filename);
                free(buffer);
                fclose(img);
                fclose(infile);
                return 1;
            }

            // Writes header data to file
            fwrite(buffer, 1, block, img);

            // increments i
            i++;

            // Frees filename
            free(filename);
        }
        // If it is not the start of JPG, write the data
        else if (img != NULL)
        {
            fwrite(buffer, 1, block, img);
        }
    }

    // Closes Files and frees memory once program is finished
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(infile);
    free(buffer);

    return 0;
}