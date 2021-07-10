#include <stdio.h>
#include <getopt.h>
#include "util/util.h"
#include "parser/BMP.h"
#include "effects/BMPeffects.h"

int main(int argc, char **argv)
{
	// allowable filters { b -> Blur, c -> Contrast, g -> Grayscal, i -> Brightness, r -> Reflect, s -> Sepia }
	char *filters = "bcgirs";

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
		fprintf(stderr, "Usage: cli.exe [flag] infile outfile\n");
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
	BMP *image = openBMP(infile);

	// Filter image
	switch (filter)
	{
		// Blur
		case 'b':
			blur(image);
			break;

		// Contrast
		case 'c':
			contrast(image, 128);
			break;

		// Grayscale
		case 'g':
			grayscale(image);
			break;

		// Reflection
		case 'r':
			reflect(image);
			break;

		// Sepia
		case 's':
			sepia(image);
			break;

		// Brightness
		case 'i':
			brightnes(image, 128);
			break;
	};

	// Writing the BMP file
	writeBMP(outfile, image);

	// closing the BMP file
	closeBMP(image);

	// closing the file pointers
	fclose(inputptr);
	fclose(outputptr);

	return 0;
};
