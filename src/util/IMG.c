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

/*
 * @file IMG.c
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This file contains the IMG function prototypes implementation from IMG.h
 * 
 */

#include "util/util.h"
#include "util/stdc.h"
#include "util/IMG.h"

// BMP to IMG
IMG *BMPtoIMG(BMP *image)
{
    // Allocating memory to the IMG
    IMG *genericImage = malloc(sizeof(IMG));
    if (genericImage == NULL)
    {
        return NULL;
    };
    // Assining height and width to the IMG
    genericImage->height = image->bi.biHeight;
    genericImage->width = image->bi.biWidth;

    // Allocating memory for the pixle map
    genericImage->pixlemap = (RGB **)calloc(image->bi.biHeight, sizeof(RGB *));
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        genericImage->pixlemap[i] = (RGB *)calloc(image->bi.biWidth, sizeof(RGB));
    }

    // Assining the value to the pixle map
    for (s64 i = 0; i < genericImage->height; i++)
    {
        for (s64 j = 0; j < genericImage->width; j++)
        {
            genericImage->pixlemap[i][j] = image->pixlemap[i][j];
        };
    };

    // Returning IMG
    return genericImage;
};

// IMG to BMP
BMP *IMGtoBMP(IMG *image, BMP *BMPimage)
{
    // If invalud parameters
    if (image == NULL || BMPimage == NULL)
    {
        return BMPimage;
    };
    // Assining height and width to the BMP image
    BMPimage->bi.biHeight = image->height;
    BMPimage->bi.biWidth = image->width;

    // Assining value to the BMP image pixle map
    for (s64 i = 0; i < BMPimage->bi.biHeight; i++)
    {
        for (s64 j = 0; j < BMPimage->bi.biWidth; j++)
        {
            BMPimage->pixlemap[i][j] = image->pixlemap[i][j];
        };
    };

    // Returning BMP image
    return BMPimage;
};

// Close IMG
void closeIMG(IMG *image)
{
    // If invalid parameter
    if (image == NULL)
    {
        return;
    };

    // Freeing the each block of height array
    for (s64 counter = 0; counter < image->height; counter++)
    {
        free(image->pixlemap[counter]);
    };

    // Freeing the Pixle map
    free(image->pixlemap);

    // Freeing the image
    free(image);

    return;
};