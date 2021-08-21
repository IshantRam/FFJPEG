#include "util/stdc.h"
#include "effects/BMPeffects.h"

// Blur
void blur(BMP *image)
{
    RGBTRIPLE clone[image->bi.biHeight][image->bi.biWidth];
    for (s32 i = 0; i < image->bi.biHeight; i++)
    {
        for (s32 j = 0; j < image->bi.biWidth; j++)
        {
            u16 finalRed = 0;
            u16 finalGreen = 0;
            u16 finalBlue = 0;
            u8 counter = 0;

            for (s8 r = -1; r <= 1; r++)
            {
                for (s8 c = -1; c <= 1; c++)
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
            clone[i][j].rgbtRed = round(finalRed / counter);
            clone[i][j].rgbtGreen = round(finalGreen / counter);
            clone[i][j].rgbtBlue = round(finalBlue / counter);
        }
    }

    for (s32 i = 0; i < image->bi.biHeight; i++)
    {
        for (s32 j = 0; j < image->bi.biWidth; j++)
        {
            image->PixleMap[i][j] = clone[i][j];
        }
    }
    return;
};

// Contrast
void contrast(BMP *image, u8 contrastlevel)
{
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        for (s64 j = 0; j < image->bi.biWidth; j++)
        {
            float factor = (259 * (contrastlevel + 255)) / (255 * (259 - contrastlevel));
            image->PixleMap[i][j].rgbtRed = wrap((s64)((factor * image->PixleMap[i][j].rgbtRed - contrastlevel) + contrastlevel));
            image->PixleMap[i][j].rgbtGreen = wrap((s64)((factor * image->PixleMap[i][j].rgbtGreen - contrastlevel) + contrastlevel));
            image->PixleMap[i][j].rgbtBlue = wrap((s64)((factor * image->PixleMap[i][j].rgbtBlue - contrastlevel) + contrastlevel));
        };
    };
    return;
};

// Brightnes
void brightnes(BMP *image, u8 brightneslevel)
{
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        for (s64 j = 0; j < image->bi.biWidth; j++)
        {
            image->PixleMap[i][j].rgbtRed = wrap((s64)image->PixleMap[i][j].rgbtRed + brightneslevel);
            image->PixleMap[i][j].rgbtGreen = wrap((s64)image->PixleMap[i][j].rgbtGreen + brightneslevel);
            image->PixleMap[i][j].rgbtBlue = wrap((s64)image->PixleMap[i][j].rgbtBlue + brightneslevel);
        };
    };
    return;
};

// Grayscale
void grayscale(BMP *image)
{
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        for (s64 j = 0; j < image->bi.biWidth; j++)
        {
            u8 avg = round((image->PixleMap[i][j].rgbtRed + image->PixleMap[i][j].rgbtGreen + image->PixleMap[i][j].rgbtBlue) / 3.00);

            image->PixleMap[i][j].rgbtRed = avg;
            image->PixleMap[i][j].rgbtGreen = avg;
            image->PixleMap[i][j].rgbtBlue = avg;
        };
    };
    return;
};

// Reflect
void reflect(BMP *image)
{
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        for (s64 j = 0; j < image->bi.biWidth / 2; j++)
        {
            RGBTRIPLE tmp = image->PixleMap[i][j];
            image->PixleMap[i][j] = image->PixleMap[i][image->bi.biWidth - j - 1];
            image->PixleMap[i][image->bi.biWidth - j - 1] = tmp;
        };
    };
    return;
};

// Sepia
void sepia(BMP *image)
{
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        for (s64 j = 0; j < image->bi.biWidth; j++)
        {
            u16 sepiaRed = round(.393 * image->PixleMap[i][j].rgbtRed + .769 * image->PixleMap[i][j].rgbtGreen + .189 * image->PixleMap[i][j].rgbtBlue);
            u16 sepiaGreen = round(.349 * image->PixleMap[i][j].rgbtRed + .686 * image->PixleMap[i][j].rgbtGreen + .168 * image->PixleMap[i][j].rgbtBlue);
            u16 sepiaBlue = round(.272 * image->PixleMap[i][j].rgbtRed + .534 * image->PixleMap[i][j].rgbtGreen + .131 * image->PixleMap[i][j].rgbtBlue);

            sepiaRed = wrap((s64)sepiaRed);
            sepiaGreen = wrap((s64)sepiaRed);
            sepiaGreen = wrap((s64)sepiaRed);

            image->PixleMap[i][j].rgbtRed = sepiaRed;
            image->PixleMap[i][j].rgbtGreen = sepiaGreen;
            image->PixleMap[i][j].rgbtBlue = sepiaBlue;
        };
    };
    return;
};