// BMP related data types
#pragma once
#ifndef BMP_H
#define BMP_H

#include "util/util.h"

/**
 * BITMAPFILEHEADER
 *
 * The BITMAPFILEHEADER structure contains information about the type, size,
 * and layout of a file that contains a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183374(VS.85).aspx.
 */
typedef struct BITMAPFILEHEADER
{
	u16 bfType;
	u32 bfSize;
	u16 bfReserved1;
	u16 bfReserved2;
	u32 bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 *
 * The BITMAPINFOHEADER structure contains information about the
 * dimensions and color format of a DIB [device-independent bitmap].
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/dd183376(VS.85).aspx.
 */
typedef struct BITMAPINFOHEADER
{
	u32 biSize;
	s32 biWidth;
	s32 biHeight;
	u16 biPlanes;
	u16 biBitCount;
	u32 biCompression;
	u32 biSizeImage;
	s32 biXPelsPerMeter;
	s32 biYPelsPerMeter;
	u32 biClrUsed;
	u32 biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * RGBTRIPLE
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */
typedef struct RGBTRIPLE
{
	u8 rgbtBlue;
	u8 rgbtGreen;
	u8 rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;

/**
 * BMP
 * 
 * This structure contains information about the image
 * BITMAPFILEHEADER, BITMAPINFOHEADER, RGBTRIPLE pixlemap
 */
typedef struct BMP
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGBTRIPLE** PixleMap;
} __attribute__((__packed__))
BMP;

/*
 * open BMP
 * 
 * The openBMP Function returns the BMP file data loaded in the BMP structure
 * which contains BITMAPFILEHEADER BITMAPINFOHEADER and RGBTRIPLE pixlemap
 * 
 */
BMP *openBMP(char *file);

/*
 * close BMP
 * 
 * The closeBMP Function frees the allocated memory for image loaded in the BMP structure
 * 
 */
void closeBMP(BMP* image);

/*
 * write BMP
 *
 * The writeBMP Function creates a new BMP image file with the arguments
 * a BMP structure which contains the information about the image (BITMAPFILEHEADER BITMAPINFOHEADER and RGBTRIPLE pixlemap)
 */
void writeBMP(char *file, BMP* image);

#endif
