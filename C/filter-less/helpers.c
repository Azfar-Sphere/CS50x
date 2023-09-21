#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avgpxl = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            avgpxl = round(avgpxl);

            image[i][j].rgbtRed = avgpxl;
            image[i][j].rgbtGreen = avgpxl;
            image[i][j].rgbtBlue = avgpxl;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sepia Formula
            float sepiaRed = (.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue);
            float sepiaGreen = (.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue);
            float sepiaBlue = (.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue);

            // Checks if the Value is greater than 255
            if (sepiaRed > 0xff)
            {
                sepiaRed = 0xff;
            }
            if (sepiaGreen > 0xff)
            {
                sepiaGreen = 0xff;
            }
            if (sepiaBlue > 0xff)
            {
                sepiaBlue = 0xff;
            }

            // Rounds up to Nearest Whole Number
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            // Assigns Pixels
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterates through each Column
    for (int i = 0; i < height; i++)
    {
        // Swaps Pixels in each Row
        for (int j = 0; j <= (width - 1) / 2; j++)
        {
            RGBTRIPLE pswap = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = pswap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int Pixel = 0;
    int Red[height * width];
    int Green[height * width];
    int Blue[height * width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float TotalPixels = 0;

            float AvgRed = 0;
            float TotalRed = 0;

            float AvgGreen = 0;
            float TotalGreen = 0;

            float AvgBlue = 0;
            float TotalBlue = 0;

            for (int z = i - 1; z <= i + 1; z++)
            {
                if (z >= 0 && z < height)
                {
                    for (int x = j - 1; x <= j + 1; x++)
                    {
                        if (x >= 0 && x < width)
                        {
                            // Calculates the Amount of Color in 3x3 Neighbouring Pixels
                            TotalRed += image[z][x].rgbtRed;
                            TotalGreen += image[z][x].rgbtGreen;
                            TotalBlue += image[z][x].rgbtBlue;
                            TotalPixels++;
                        }
                    }
                }
            }

            if (TotalPixels != 0)
            {
                // Finds Average Color
                AvgRed = TotalRed / TotalPixels;
                AvgRed = (AvgRed > 0xff) ? 0xff : AvgRed;
                AvgGreen = TotalGreen / TotalPixels;
                AvgGreen = (AvgGreen > 0xff) ? 0xff : AvgGreen;
                AvgBlue = TotalBlue / TotalPixels;
                AvgBlue = (AvgBlue > 0xff) ? 0xff : AvgBlue;

                // Rounds Up to Whole Number
                AvgRed = round(AvgRed);
                AvgGreen = round(AvgGreen);
                AvgBlue = round(AvgBlue);

                // Stores Value of Each Color in Array
                Red[Pixel] = AvgRed;
                Green[Pixel] = AvgGreen;
                Blue[Pixel] = AvgBlue;
                Pixel++;
            }
        }
    }

    // Assigns Color Value to each Pixel
    Pixel = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = Red[Pixel];
            image[i][j].rgbtGreen = Green[Pixel];
            image[i][j].rgbtBlue = Blue[Pixel];
            Pixel++;
        }
    }
    return;
}
