/**
 * @file FFJPEG.h
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief Multimedia converter for FFJPEG.
 * 
 */

#include "util/stdc.h"
#include "util/util.h"
#include "util/IMG.h"
#include "parser/BMP.h"
#include "effects/effects.h"

int main(int argc, char **argv)
{
	// Allowable filters { b -> Blur, c -> Contrast [level], g -> Grayscal, i -> Brightness [level], r -> Reflect, s -> Sepia }
	char *filters = "bc:gi:rs";

	// Get option flag and check validity
	char option = getopt(argc, argv, filters);

	// Unknow Option
	if (option == '?')
	{
		fprintf(stderr, "Usage: %s [flag] ... infile outfile\n", argv[0]);
		return EXIT_FAILURE;
	};

	// Ensure only one option
	if (getopt(argc, argv, filters) != -1)
	{
		fprintf(stderr, "Only one option allowed.\n");
		return EXIT_FAILURE;
	};

	// Ensure proper usage
	if (argc != optind + 2)
	{
		fprintf(stderr, "Usage: %s [flag] ... infile outfile\n", argv[0]);
		return EXIT_FAILURE;
	};

	// Remember filenames
	char *infile = argv[optind];
	char *outfile = argv[optind + 1];

	// Open input file
	FILE *inputptr = fopen(infile, "r");
	if (inputptr == NULL)
	{
		fprintf(stderr, "Could not open %s.\n", infile);
		return EXIT_FAILURE;
	};

	// Open output file
	FILE *outputptr = fopen(outfile, "w");
	if (outputptr == NULL)
	{
		fclose(inputptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return EXIT_FAILURE;
	};

	// Closing the file pointers
	fclose(inputptr);
	fclose(outputptr);
	
	// Confirm the image is supported by FFJPEG
	u8 type = getType(infile);
	if (type != 1)
	{
		fprintf(stderr, "Unsupported file format %s\n", infile);
		return EXIT_FAILURE;
	};

	// Open the image
	BMP *BMPimage = openBMP(infile);
	if (BMPimage == NULL)
	{
		return EXIT_FAILURE;
	};

	// Moving the image to generic image struct
	IMG *image = BMPtoIMG(BMPimage);
	if (image == NULL)
	{
		return EXIT_FAILURE;
	};

	// filter image
	switch (option)
	{
		// Blur
		case 'b':
			blur(image);
			break;

		// Contrast [level]
		case 'c':
			contrast(image, atoi(optarg));
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

		// Brightness [level]
		case 'i':
			brightnes(image, atoi(optarg));
			break;
	};

	// Moving IMG to BMP 
	BMPimage = IMGtoBMP(image, BMPimage);

	// Writing the BMP file
	writeBMP(outfile, BMPimage);

	// Closing the BMP file
	closeBMP(BMPimage);

	// Closing the IMG file
	closeIMG(image);

	return EXIT_SUCCESS;
};
