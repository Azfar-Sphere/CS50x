#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Error! Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error! Incorrect input file!");
        return 1;
    }

    // Read header
    WAVHEADER wv;
    fread(&wv, sizeof(WAVHEADER), 1, infile);

    // Use check_format to ensure WAV format
    if (check_format(wv) == 0)
    {
        printf("Error! Wrong Format\n");
        return 1;
    }

    // Open output file for writing
    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL)
    {
        printf("Error! Incorrect Output file!");
        return 1;
    }

    // Write header to file
    fwrite(&wv, sizeof(WAVHEADER), 1, outfile);

    // Use get_block_size to calculate size of block
    int blocksize = get_block_size(wv);

    // Write reversed audio to file

    // Count Numbers of Blocks
    int NumBlocks = (wv.subchunk2Size / blocksize);

    // Reads each Block of Audio and stores in an Array
    WORD *blocks[NumBlocks];

    fseek(infile, 44, SEEK_SET);

    for (int i = 0; i < (NumBlocks); i++)
    {
        blocks[i] = malloc(blocksize);
        if (blocks[i] == NULL)
        {
            printf("Memory Allocation Failure\n");
            return 2;
        }

        fread(blocks[i], blocksize, 1, infile);
        if (ftell(infile) == 44 + wv.subchunk2Size)
        {
            break;
        }
    }

    // Writes in reverse order the Blocks of Audio
    fseek(outfile, 44, SEEK_SET);
    for (int i = NumBlocks - 1; i >= 0; i--)
    {
        fwrite(blocks[i], blocksize, 1, outfile);

        if (ftell(outfile) == 44 + wv.subchunk2Size)
        {
            break;
        }
        free(blocks[i]);
    }

    fclose(infile);
    fclose(outfile);
}

int check_format(WAVHEADER header)
{
    char *wave = malloc(5);

    if (wave == NULL)
    {
        printf("Memory Allocation Failure\n");
        return 2;
    }

    for (int i = 0; i < 4; i++)
    {
        wave[i] = header.format[i];
    }
    wave[4] = '\0';

    if (strcmp(wave, "WAVE") == 0)
    {
        free(wave);
        return 1;
    }
    else
    {
        free(wave);
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    int blocksize = (header.numChannels * (header.bitsPerSample / 8));
    return blocksize;
}