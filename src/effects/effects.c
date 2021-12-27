/**
 * @file effects.c
 * @author Ishant Ram
 * @date 27th December 2021
 * @brief This file contains the effect function prototypes implementation from effects.h
 * 
 */

#include "util/stdc.h"
#include "effects/effects.h"

// Blur
void blur(IMG *image)
{
    RGB clone[image->height][image->width];
    for (s32 i = 0; i < image->height; i++)
    {
        for (s32 j = 0; j < image->width; j++)
        {
            u16 finalRed = 0;
            u16 finalGreen = 0;
            u16 finalBlue = 0;
            u8 counter = 0;

            for (s8 r = -1; r <= 1; r++)
            {
                for (s8 c = -1; c <= 1; c++)
                {
                    if (i + r >= 0 && i + r <= image->height - 1 && j + c >= 0 && j + c <= image->width - 1)
                    {
                        finalRed = finalRed + image->pixlemap[i + r][j + c].R;
                        finalGreen = finalGreen + image->pixlemap[i + r][j + c].G;
                        finalBlue = finalBlue + image->pixlemap[i + r][j + c].B;
                        counter++;
                    }
                }
            }
            clone[i][j].R = round(finalRed / counter);
            clone[i][j].G = round(finalGreen / counter);
            clone[i][j].B = round(finalBlue / counter);
        }
    }

    for (s32 i = 0; i < image->height; i++)
    {
        for (s32 j = 0; j < image->width; j++)
        {
            image->pixlemap[i][j] = clone[i][j];
        }
    }
    return;
};

// Contrast
void contrast(IMG *image, u8 contrastlevel)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            f32 factor = (259 * (contrastlevel + 255)) / (255 * (259 - contrastlevel));
            image->pixlemap[i][j].R = wrap((s64)((factor * image->pixlemap[i][j].R - contrastlevel) + contrastlevel));
            image->pixlemap[i][j].G = wrap((s64)((factor * image->pixlemap[i][j].G - contrastlevel) + contrastlevel));
            image->pixlemap[i][j].B = wrap((s64)((factor * image->pixlemap[i][j].B - contrastlevel) + contrastlevel));
        };
    };
    return;
};

// Brightnes
void brightnes(IMG *image, u8 brightneslevel)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            image->pixlemap[i][j].R = wrap((s64)image->pixlemap[i][j].R + brightneslevel);
            image->pixlemap[i][j].G = wrap((s64)image->pixlemap[i][j].G + brightneslevel);
            image->pixlemap[i][j].B = wrap((s64)image->pixlemap[i][j].B + brightneslevel);
        };
    };
    return;
};

// Grayscale
void grayscale(IMG *image)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            u8 avg = round((image->pixlemap[i][j].R + image->pixlemap[i][j].G + image->pixlemap[i][j].B) / 3.00);

            image->pixlemap[i][j].R = avg;
            image->pixlemap[i][j].G = avg;
            image->pixlemap[i][j].B = avg;
        };
    };
    return;
};

// Reflect
void reflect(IMG *image)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width / 2; j++)
        {
            RGB tmp = image->pixlemap[i][j];
            image->pixlemap[i][j] = image->pixlemap[i][image->width - j - 1];
            image->pixlemap[i][image->width - j - 1] = tmp;
        };
    };
    return;
};

// Sepia
void sepia(IMG *image)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            int sepiaRed = round(.393 * image->pixlemap[i][j].R + .769 * image->pixlemap[i][j].G + .189 * image->pixlemap[i][j].B);
            int sepiaGreen = round(.349 * image->pixlemap[i][j].R + .686 * image->pixlemap[i][j].G + .168 * image->pixlemap[i][j].B);
            int sepiaBlue = round(.272 * image->pixlemap[i][j].R + .534 * image->pixlemap[i][j].G + .131 * image->pixlemap[i][j].B);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = (long int)sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen = (long int)sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = (long int)sepiaBlue;
            }

            image->pixlemap[i][j].R = sepiaRed;
            image->pixlemap[i][j].G = sepiaGreen;
            image->pixlemap[i][j].B = sepiaBlue;
        };
    };
    return;
};

// Red
void red(IMG *image)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            image->pixlemap[i][j].R = 255; 
        };
    };

    return;
};

// Green
void green(IMG *image)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            image->pixlemap[i][j].G = 255;
        };
    };

    return;
};

// Blue
void blue(IMG *image)
{
    for (s64 i = 0; i < image->height; i++)
    {
        for (s64 j = 0; j < image->width; j++)
        {
            image->pixlemap[i][j].B = 255; 
        };
    };
    return;
};

// Debug
void debug(IMG *image)
{
    return;
};
