#include "helpers.h"
#include <math.h>

int SobelTableX(int height, int width, int y, int x);
int SobelTableY(int height, int width, int y, int x);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgp = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avgp;
            image[i][j].rgbtGreen = avgp;
            image[i][j].rgbtBlue = avgp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE swap = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = swap;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Intializes an Array to store each final value of each pixel
    int gRed[height * width];
    int gGreen[height * width];
    int gBlue[height * width];

    // Counts Pixels
    int Pixel = 0;

    // Iterates through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Intializes gx and gy color values
            float gxRed = 0;
            float gxGreen = 0;
            float gxBlue = 0;

            float gyRed = 0;
            float gyGreen = 0;
            float gyBlue = 0;

            for (int z = i - 1; z <= i + 1; z++)
            {
                if (z >= 0 && z < height)
                {
                    for (int y = j - 1; y <= j + 1; y++)
                    {
                        if (y >= 0 && y < width)
                        {
                            // Calculates gx and gy values, calls SobelTable which store values on where the pixel is
                            gxRed += (image[z][y].rgbtRed * SobelTableX(i, j, z, y));
                            gxGreen += (image[z][y].rgbtGreen * SobelTableX(i, j, z, y));
                            gxBlue += (image[z][y].rgbtBlue * SobelTableX(i, j, z, y));

                            gyRed += (image[z][y].rgbtRed * SobelTableY(i, j, z, y));
                            gyGreen += (image[z][y].rgbtGreen * SobelTableY(i, j, z, y));
                            gyBlue += (image[z][y].rgbtBlue * SobelTableY(i, j, z, y));
                        }
                    }
                }
            }

            // Calcultes final g value for that particular pixel
            gRed[Pixel] = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            gGreen[Pixel] = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            gBlue[Pixel] = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            // Checks if it is greater than 255 or not
            gRed[Pixel] = (gRed[Pixel] > 0xff) ? 0xff : gRed[Pixel];
            gGreen[Pixel] = (gGreen[Pixel] > 0xff) ? 0xff : gGreen[Pixel];
            gBlue[Pixel] = (gBlue[Pixel] > 0xff) ? 0xff : gBlue[Pixel];

            // increments pixel
            Pixel++;
        }
    }

    Pixel = 0;

    // Assigns final color values to each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = gRed[Pixel];
            image[i][j].rgbtGreen = gGreen[Pixel];
            image[i][j].rgbtBlue = gBlue[Pixel];

            Pixel++;
        }
    }

    return;
}

// Return Gx Values
int SobelTableX(int height, int width, int y, int x)
{
    // Checks which pixel in the 3x3 grid is being taken into account
    switch (y - height)
    {
        case -1:
            switch (x - width)
            {
                case -1:
                    return -1;
                case 0:
                    return 0;
                case 1:
                    return 1;
            }

        case 0:
            switch (x - width)
            {
                case -1:
                    return -2;
                case 0:
                    return 0;
                case 1:
                    return 2;
            }
        case 1:
            switch (x - width)
            {
                case -1:
                    return -1;
                case 0:
                    return 0;
                case 1:
                    return 1;
            }
    }

    return 0;
}

// Return Gy Values
int SobelTableY(int height, int width, int y, int x)
{
    // Checks which pixel in the 3x3 grid is being taken into account
    switch (y - height)
    {
        case -1:
            switch (x - width)
            {
                case -1:
                    return -1;
                case 0:
                    return -2;
                case 1:
                    return -1;
            }

        case 0:
            switch (x - width)
            {
                case -1:
                    return 0;
                case 0:
                    return 0;
                case 1:
                    return 0;
            }
        case 1:
            switch (x - width)
            {
                case -1:
                    return 1;
                case 0:
                    return 2;
                case 1:
                    return 1;
            }
    }

    return 0;
}
