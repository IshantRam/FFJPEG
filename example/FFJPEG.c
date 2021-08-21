#include "util/stdc.h"
#include "util/util.h"
#include "parser/BMP.h"
#include "effects/BMPeffects.h"

int main(int argc, char **argv)
{
	// allowable filters { b -> Blur, c -> Contrast [level], g -> Grayscal, i -> Brightness [level], r -> Reflect, s -> Sepia }
	char *filters = "bc:gi:rs";
	
	// Get option flag and check validity
	char option = getopt(argc, argv, filters);
	
	if (option == '?')
	{
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

	// Opening the BMP file and reading the file
	BMP *image = openBMP(infile);

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

	// Writing the BMP file
	writeBMP(outfile, image);

	// Closing the BMP file
	closeBMP(image);

	// Closing the file pointers
	fclose(inputptr);
	fclose(outputptr);

	return EXIT_SUCCESS;
};
