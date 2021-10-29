/**
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