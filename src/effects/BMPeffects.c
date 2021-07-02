#include "effects/BMPeffects.h"
#include <math.h>

// Grayscale
void grayscale(BMP *image)
{
    for (int i = 0; i < image->bi.biHeight; i++)
    {
        for (int j = 0; j < image->bi.biWidth; j++)
        {
            int avg = round((image->PixleMap[i][j].rgbtRed + image->PixleMap[i][j].rgbtGreen + image->PixleMap[i][j].rgbtBlue) / 3.00);

            image->PixleMap[i][j].rgbtRed = avg;
            image->PixleMap[i][j].rgbtGreen = avg;
            image->PixleMap[i][j].rgbtBlue = avg;
        };
    };
    return;
};

// Sepia
void sepia(BMP *image)
{
    for (int i = 0; i < image->bi.biHeight; i++)
    {
        for (int j = 0; j < image->bi.biWidth; j++)
        {
            int sepiaRed = round(.393 * image->PixleMap[i][j].rgbtRed + .769 * image->PixleMap[i][j].rgbtGreen + .189 * image->PixleMap[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image->PixleMap[i][j].rgbtRed + .686 * image->PixleMap[i][j].rgbtGreen + .168 * image->PixleMap[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image->PixleMap[i][j].rgbtRed + .534 * image->PixleMap[i][j].rgbtGreen + .131 * image->PixleMap[i][j].rgbtBlue);

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

            image->PixleMap[i][j].rgbtRed = sepiaRed;
            image->PixleMap[i][j].rgbtGreen = sepiaGreen;
            image->PixleMap[i][j].rgbtBlue = sepiaBlue;
        };
    };
    return;
};

// Reflect
void reflect(BMP *image)
{
    for (int i = 0; i < image->bi.biHeight; i++)
    {
        for (int j = 0; j < image->bi.biWidth / 2; j++)
        {
            RGBTRIPLE tmp = image->PixleMap[i][j];
            image->PixleMap[i][j] = image->PixleMap[i][image->bi.biWidth - j - 1];
            image->PixleMap[i][image->bi.biWidth - j - 1] = tmp;
        };
    };
    return;
};

// Blur
void blur(BMP *image)
{
    RGBTRIPLE clone[image->bi.biHeight][image->bi.biWidth];
    for (int i = 0; i < image->bi.biHeight; i++)
    {
        for (int j = 0; j < image->bi.biWidth; j++)
        {
            int finalRed = 0;
            int finalGreen = 0;
            int finalBlue = 0;
            int counter = 0;

            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    if (i + r >= 0 && i + r <= image->bi.biHeight - 1 && j + c >= 0 && j + c <= image->bi.biWidth - 1)
                    {
                        finalRed = finalRed + image->PixleMap[i + r][j + c].rgbtRed;
                        finalGreen = finalGreen + image->PixleMap[i + r][j + c].rgbtGreen;
                        finalBlue = finalBlue + image->PixleMap[i + r][j + c].rgbtBlue;
                        counter++;
                    }
                }
            }
            clone[i][j].rgbtRed = (int)round((float)finalRed / (float)counter);
            clone[i][j].rgbtGreen = (int)round((float)finalGreen / (float)counter);
            clone[i][j].rgbtBlue = (int)round((float)finalBlue / (float)counter);
        }
    }

    for (int i = 0; i < image->bi.biHeight; i++)
    {
        for (int j = 0; j < image->bi.biWidth; j++)
        {
            image->PixleMap[i][j] = clone[i][j];
        }
    }
    return;
};
