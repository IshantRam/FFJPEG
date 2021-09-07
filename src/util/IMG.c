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

#include "util/util.h"
#include "util/stdc.h"
#include "util/IMG.h"

IMG *BMPtoIMG(BMP *image)
{
    IMG *genericImage = malloc(sizeof(IMG));
    if (genericImage == NULL)
    {
        return NULL;
    };
    genericImage->height = image->bi.biHeight;
    genericImage->width = image->bi.biWidth;

    genericImage->pixlemap = (RGB **)calloc(image->bi.biHeight, sizeof(RGB *));
    for (s64 i = 0; i < image->bi.biHeight; i++)
    {
        genericImage->pixlemap[i] = (RGB *)calloc(image->bi.biWidth, sizeof(RGB));
    }

    for (s64 i = 0; i < genericImage->height; i++)
    {
        for (s64 j = 0; j < genericImage->width; j++)
        {
            genericImage->pixlemap[i][j] = image->pixlemap[i][j];
        };
    };

    return genericImage;
};

BMP *IMGtoBMP(IMG *image, BMP *BMPimage)
{
    if (image == NULL || BMPimage == NULL)
    {
        return BMPimage;
    };
    BMPimage->bi.biHeight = image->height;
    BMPimage->bi.biWidth = image->width;

    for (s64 i = 0; i < BMPimage->bi.biHeight; i++)
    {
        for (s64 j = 0; j < BMPimage->bi.biWidth; j++)
        {
            BMPimage->pixlemap[i][j] = image->pixlemap[i][j];
        };
    };

    return BMPimage;
};

void closeIMG(IMG *image)
{
    if (image == NULL)
    {
        return;
    };

    for (s64 counter = 0; counter < image->height; counter++)
    {
        free(image->pixlemap[counter]);
    };
    
    free(image->pixlemap);

    free(image);

    return;
};