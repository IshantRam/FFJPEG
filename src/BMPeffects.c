#include "effects/BMPeffects.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE **image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        };
    };
    return;
};

void sepia(int height, int width, RGBTRIPLE **image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = (long int)sepiaRed;
            };
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen = (long int)sepiaGreen;
            };
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = (long int)sepiaBlue;
            };

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        };
    };
    return;
};

void reflect(int height, int width, RGBTRIPLE **image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        };
    };
    return;
};

void blur(int height, int width, RGBTRIPLE **image)
{
    RGBTRIPLE clone[height][width];
    // First 2 loops iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int finalRed = 0;
            int finalGreen = 0;
            int finalBlue = 0;
            int counter = 0;

            // Iterate through each neighbor around the pixel you're looking at
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    // If the i-value or j-value is invalid, ignore the pixel
                    if (i + r >= 0 && i + r <= height - 1 && j + c >= 0 && j + c <= width - 1)
                    {
                        finalRed = finalRed + image[i + r][j + c].rgbtRed;
                        finalGreen = finalGreen + image[i + r][j + c].rgbtGreen;
                        finalBlue = finalBlue + image[i + r][j + c].rgbtBlue;
                        counter++;
                    }
                }
            }
            // At the end of looking at all the neighbors, total up and average out the pixel's triple values and store in temp image
            clone[i][j].rgbtRed = (int)round((float)finalRed / (float)counter);
            clone[i][j].rgbtGreen = (int)round((float)finalGreen / (float)counter);
            clone[i][j].rgbtBlue = (int)round((float)finalBlue / (float)counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = clone[i][j];
        }
    }
    return;
};
