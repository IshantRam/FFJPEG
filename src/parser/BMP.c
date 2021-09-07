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
 * @file BMP.c
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This file contains the BMP function prototypes implementation from BMP.h
 * 
 */

#include "util/stdc.h"
#include "util/util.h"
#include "parser/BMP.h"

// Open BMP
BMP *openBMP(char *file)
{
	// Opening the file in read byte mode
	FILE *filePTR = fopen(file, "rb");
	if (filePTR == NULL)
	{
		fprintf(stderr, "Could not open %s\n", file);
		return NULL;
	};

	// Allocating memory for image
	BMP *image = malloc(sizeof(BMP));
	if (image == NULL)
	{
		fclose(filePTR);
		return NULL;
	};

	// Read file's BITMAPFILEHEADER
	fread(&image->bf, sizeof(BITMAPFILEHEADER), 1, filePTR);

	// Read file's BITMAPINFOHEADER
	fread(&image->bi, sizeof(BITMAPINFOHEADER), 1, filePTR);

	// Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (image->bf.bfType != 0x4d42 || image->bf.bfOffBits != 54 || image->bi.biSize != 40 || image->bi.biBitCount != 24 || image->bi.biCompression != 0)
	{
		fprintf(stderr, "Invalid image\n");
		fclose(filePTR);
		return NULL;
	};

	// Allocate memory for image->pixlemap
	image->pixlemap = (RGB **)calloc(image->bi.biHeight, sizeof(RGB *));
	for (s64 i = 0; i < image->bi.biHeight; i++)
	{
		image->pixlemap[i] = (RGB *)calloc(image->bi.biWidth, sizeof(RGB));
	}

	// Determine padding for scanlines
	u32 padding = (4 - (image->bi.biWidth * sizeof(RGB)) % 4) % 4;

	// Iterate over infile's scanlines
	for (s64 counter = 0; counter < image->bi.biHeight; counter++)
	{
		// Read row into pixel array
		fread(image->pixlemap[counter], sizeof(RGB), image->bi.biWidth, filePTR);

		// Skip over padding
		fseek(filePTR, padding, SEEK_CUR);
	};

	// Closing the file pointer
	fclose(filePTR);

	// returning BMP image
	return image;
};

// close BMP
void closeBMP(BMP *image)
{
	// if image is NULL
	if (image == NULL)
	{
		fprintf(stderr, "Invalid image\n");
		return;
	};

	// looping over the pixle map and freeing memory of each array block
	for (s64 i = 0; i < image->bi.biHeight; i++)
	{
		free(image->pixlemap[i]);
	};
	// freeing the memory of the image->pixlemap array
	free(image->pixlemap);

	// freeing the memory of image
	free(image);

	return;
};

void writeBMP(char *file, BMP *image)
{
	// Opening the file in write byte mode
	FILE *filePTR = fopen(file, "wb");
	if (filePTR == NULL)
	{
		fprintf(stderr, "Could not open %s\n", file);
		return;
	};

	// Write outfile's BITMAPFILEHEADER
	fwrite(&image->bf, sizeof(BITMAPFILEHEADER), 1, filePTR);

	// Write outfile's BITMAPINFOHEADER
	fwrite(&image->bi, sizeof(BITMAPINFOHEADER), 1, filePTR);

	u32 padding = (4 - (image->bi.biWidth * sizeof(RGB)) % 4) % 4;
	for (s64 i = 0; i < image->bi.biHeight; i++)
	{
		// Write row to outfile
		fwrite(image->pixlemap[i], sizeof(RGB), image->bi.biWidth, filePTR);

		// Write padding at end of row
		for (u32 k = 0; k < padding; k++)
		{
			fputc(0x00, filePTR);
		};
	};

	// Closing the file pointer
	fclose(filePTR);

	return;
};
