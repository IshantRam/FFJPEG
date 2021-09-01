/* 
 * Copyright (c) 2021 Ishant Ram
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include "util/stdc.h"
#include "effects/effects.h"

// Blur
void blur(BMP *image)
{
    RGB clone[image->bi.biHeight][image->bi.biWidth];
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
                        finalRed = finalRed + image->pixlemap[i + r][j + c].red;
                        finalGreen = finalGreen + image->pixlemap[i + r][j + c].green;
                        finalBlue = finalBlue + image->pixlemap[i + r][j + c].blue;
                        counter++;
                    }
                }
            }
            clone[i][j].red = round(finalRed / counter);
            clone[i][j].green = round(finalGreen / counter);
            clone[i][j].blue = round(finalBlue / counter);
        }
    }

    for (s32 i = 0; i < image->bi.biHeight; i++)
    {
        for (s32 j = 0; j < image->bi.biWidth; j++)
        {
            image->pixlemap[i][j] = clone[i][j];
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
            image->pixlemap[i][j].red = wrap((s64)((factor * image->pixlemap[i][j].red - contrastlevel) + contrastlevel));
            image->pixlemap[i][j].green = wrap((s64)((factor * image->pixlemap[i][j].green - contrastlevel) + contrastlevel));
            image->pixlemap[i][j].blue = wrap((s64)((factor * image->pixlemap[i][j].blue - contrastlevel) + contrastlevel));
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
            image->pixlemap[i][j].red = wrap((s64)image->pixlemap[i][j].red + brightneslevel);
            image->pixlemap[i][j].green = wrap((s64)image->pixlemap[i][j].green + brightneslevel);
            image->pixlemap[i][j].blue = wrap((s64)image->pixlemap[i][j].blue + brightneslevel);
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
            u8 avg = round((image->pixlemap[i][j].red + image->pixlemap[i][j].green + image->pixlemap[i][j].blue) / 3.00);

            image->pixlemap[i][j].red = avg;
            image->pixlemap[i][j].green = avg;
            image->pixlemap[i][j].blue = avg;
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
            RGB tmp = image->pixlemap[i][j];
            image->pixlemap[i][j] = image->pixlemap[i][image->bi.biWidth - j - 1];
            image->pixlemap[i][image->bi.biWidth - j - 1] = tmp;
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
            u16 sepiaRed = round(.393 * image->pixlemap[i][j].red + .769 * image->pixlemap[i][j].green + .189 * image->pixlemap[i][j].blue);
            u16 sepiaGreen = round(.349 * image->pixlemap[i][j].red + .686 * image->pixlemap[i][j].green + .168 * image->pixlemap[i][j].blue);
            u16 sepiaBlue = round(.272 * image->pixlemap[i][j].red + .534 * image->pixlemap[i][j].green + .131 * image->pixlemap[i][j].blue);

            sepiaRed = wrap((s64)sepiaRed);
            sepiaGreen = wrap((s64)sepiaRed);
            sepiaGreen = wrap((s64)sepiaRed);

            image->pixlemap[i][j].red = sepiaRed;
            image->pixlemap[i][j].green = sepiaGreen;
            image->pixlemap[i][j].blue = sepiaBlue;
        };
    };
    return;
};