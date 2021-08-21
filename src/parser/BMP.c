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
		return NULL;
	};

	// Allocating memory for image
	BMP *image = malloc(sizeof(BMP));
	if (image == NULL)
	{
		return NULL;
	};

	// Read file's BITMAPFILEHEADER
	fread(&image->bf, sizeof(BITMAPFILEHEADER), 1, filePTR);

	// Read file's BITMAPINFOHEADER
	fread(&image->bi, sizeof(BITMAPINFOHEADER), 1, filePTR);

	// Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
	if (image->bf.bfType != 0x4d42 || image->bf.bfOffBits != 54 || image->bi.biSize != 40 || image->bi.biBitCount != 24 || image->bi.biCompression != 0)
	{
		fclose(filePTR);
		return NULL;
	};

	// Allocate memory for image->PixleMap
	image->PixleMap = (RGBTRIPLE **)calloc(image->bi.biHeight, sizeof(RGBTRIPLE *));
	for (s64 i = 0; i < image->bi.biHeight; i++)
	{
		image->PixleMap[i] = (RGBTRIPLE *)calloc(image->bi.biWidth, sizeof(RGBTRIPLE));
	}

	// Determine padding for scanlines
	u32 padding = (4 - (image->bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	// Iterate over infile's scanlines
	for (s64 counter = 0; counter < image->bi.biHeight; counter++)
	{
		// Read row into pixel array
		fread(image->PixleMap[counter], sizeof(RGBTRIPLE), image->bi.biWidth, filePTR);

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
		return;
	};

	// looping over the pixle map and freeing memory of each array block
	for (s64 i = 0; i < image->bi.biHeight; i++)
	{
		free(image->PixleMap[i]);
	};
	// freeing the memory of the image->PixleMap array
	free(image->PixleMap);

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
		return;
	};

	// Write outfile's BITMAPFILEHEADER
	fwrite(&image->bf, sizeof(BITMAPFILEHEADER), 1, filePTR);

	// Write outfile's BITMAPINFOHEADER
	fwrite(&image->bi, sizeof(BITMAPINFOHEADER), 1, filePTR);

	u32 padding = (4 - (image->bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	for (s64 i = 0; i < image->bi.biHeight; i++)
	{
		// Write row to outfile
		fwrite(image->PixleMap[i], sizeof(RGBTRIPLE), image->bi.biWidth, filePTR);

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
