#include <stdio.h>
#include <getopt.h>
#include "parser/BMP.h"
#include "effects/BMPeffects.h"

int main(int argc, char **argv)
{
	// allowable filters
	char *filters = "grs";

	// Get filter flag and check validity
	char filter = getopt(argc, argv, filters);
	if (filter == '?')
	{
		fprintf(stderr, "Invalid filter.\n");
		return 1;
	};
	
	// Ensure only one filter
	if (getopt(argc, argv, filters) != -1)
	{
		fprintf(stderr, "Only one filter allowed.\n");
		return 1;
	};

	// Ensure proper usage
	if (argc != optind + 2)
	{
		fprintf(stderr, "Usage: filter [flag] infile outfile\n");
		return 1;
	};

	// Remember filenames
	char *infile = argv[optind];
	char *outfile = argv[optind + 1];

	// Open input file
	FILE *inputptr = fopen(infile, "r");
	if (inputptr == NULL)
	{
		fprintf(stderr, "Could not open %s.\n", infile);
		return 1;
	};

	// Open output file
	FILE *outputptr = fopen(outfile, "wb");
	if (outputptr == NULL)
	{
		fclose(inputptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 1;
	};
	
	// Opening the BMP file and reading the file
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGBTRIPLE** image = openBMP(infile, &bf, &bi);
	
	// Filter image
	switch (filter)
	{
		// Grayscale
		case 'g':
			grayscale(bi.biHeight, bi.biWidth, image);
			break;

		// Reflection
		case 'r':
			reflect(bi.biHeight, bi.biWidth, image);
			break;

		// Sepia
		case 's':
			sepia(bi.biHeight, bi.biWidth, image);
			break;
	};
	
	// Writing the BMP file
	writeBMP(outfile, &bf, &bi, image);
	
	// closing the BMP file
	closeBMP(image, bi.biHeight);
	
	// closing the file
	fclose(inputptr);
	fclose(outputptr);

	return 0;
};
