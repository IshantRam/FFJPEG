#include "parser/BMP.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

RGBTRIPLE **openBMP(char *file, BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi)
{
	// Opening the file in read byte mode
	FILE *filePTR = fopen(file, "rb");
	if (filePTR == NULL)
	{
		return NULL;
	};

	// Read file's BITMAPFILEHEADER
	fread(bf, sizeof(BITMAPFILEHEADER), 1, filePTR);

	// Read file's BITMAPINFOHEADER
	fread(bi, sizeof(BITMAPINFOHEADER), 1, filePTR);

	// Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (bf->bfType != 0x4d42 || bf->bfOffBits != 54 || bi->biSize != 40 || bi->biBitCount != 24 || bi->biCompression != 0)
	{
		fclose(filePTR);
		return NULL;
	};

	s64 height = bi->biHeight;
	s64 width = bi->biWidth;

	// Allocate memory for image
	RGBTRIPLE **image = (RGBTRIPLE **)calloc(height, sizeof(RGBTRIPLE *));
	for (int i = 0; i < height; i++)
	{
		image[i] = (RGBTRIPLE *)calloc(width, sizeof(RGBTRIPLE));
	}

	// Determine padding for scanlines
	int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

	// Iterate over infile's scanlines
	for (int counter = 0; counter < height; counter++)
	{
		// Read row into pixel array
		fread(image[counter], sizeof(RGBTRIPLE), width, filePTR);

		// Skip over padding
		fseek(filePTR, padding, SEEK_CUR);
	};

	fclose(filePTR);

	return image;
};

void closeBMP(RGBTRIPLE **image, int height)
{
	for (int i = 0; i < height; i++)
	{
		free(image[i]);
	};

	free(image);
};

void writeBMP(char *file, BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi, RGBTRIPLE** image)
{
	// Opening the file in read byte mode
	FILE *filePTR = fopen(file, "wb");

	// Write outfile's BITMAPFILEHEADER
	fwrite(bf, sizeof(BITMAPFILEHEADER), 1, filePTR);

	// Write outfile's BITMAPINFOHEADER
	fwrite(bi, sizeof(BITMAPINFOHEADER), 1, filePTR);

	int padding = (4 - (bi->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	for (int i = 0; i < bi->biHeight; i++)
	{
		// Write row to outfile
		fwrite(image[i], sizeof(RGBTRIPLE), bi->biWidth, filePTR);

		// Write padding at end of row
		for (int k = 0; k < padding; k++)
		{
			fputc(0x00, filePTR);
		};
	};

	return;
};
