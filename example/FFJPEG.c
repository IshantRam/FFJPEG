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

	// Confirm the image is supported by FFJPEG
	u8 type = getType(infile);
	if (type != 1)
	{
		fclose(inputptr);
		fclose(outputptr);
		fprintf(stderr, "Unsupported file format %s\n", infile);
		return EXIT_FAILURE;
	};

	BMP *BMPimage = openBMP(infile);
	if (BMPimage == NULL)
	{
		return EXIT_FAILURE;
	};

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

	// Closing the file pointers
	fclose(inputptr);
	fclose(outputptr);

	return EXIT_SUCCESS;
};
