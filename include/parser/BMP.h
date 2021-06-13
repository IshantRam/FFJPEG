// BMP-related data types based on Microsoft's own
#pragma once
#ifndef BMP_H
#define BMP_H

#include "util.h"

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

/*
 * open BMP
 * 
 * The openBMP Function output the each RGB pixel value of the given BMP file with 
 * BITMAPFILEHEADER and BITMAPINFOHEADER header
 * 
 * Adapted from https://www.vbforums.com/showthread.php?261522-C-C-Loading-Bitmap-Files-%28Manually%29
 * 
 */
RGBTRIPLE **openBMP(char *file, BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi);

/*
 * close BMP
 * 
 * The closeBMP Function frees the allocated memory for image
 * 
 * Adapted from https://www.vbforums.com/showthread.php?261522-C-C-Loading-Bitmap-Files-%28Manually%29
 * 
 */
void closeBMP(RGBTRIPLE **image, int height);

/*
 * write BMP
 *
 * The writeBMP Function creates a new BMP image file with the arguments
 * BITMAPFILEHEADER, BITMAPINFOHEADER and RGB image array
 */
void writeBMP(char *file, BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi, RGBTRIPLE **image);

#endif
