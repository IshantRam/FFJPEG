/*
 * @file BMP.h
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This file contains BMP related data types and function prototypes
 * 
 */

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
 * 
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
 * 
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
 * BMP
 * 
 * This structure contains information about the image
 * BITMAPFILEHEADER, BITMAPINFOHEADER, RGBTRIPLE pixlemap
 * 
 */
typedef struct BMP
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	RGB **pixlemap;
} __attribute__((__packed__))
BMP;

/*
 * open BMP
 * 
 * The openBMP Function returns the BMP file data loaded in the BMP structure
 * which contains BITMAPFILEHEADER BITMAPINFOHEADER and RGB pixlemap
 * 
 * @param File name
 * @return BMP struct
 * 
 */
BMP *openBMP(char *file);

/*
 * close BMP
 * 
 * The closeBMP Function frees the allocated memory for image loaded in the BMP structure
 * 
 * @param BMP struct loaded with data
 * @return Void
 * 
 */
void closeBMP(BMP *image);

/*
 * write BMP
 *
 * The writeBMP Function creates a new BMP image with the arguments
 * a BMP structure which contains the information about the image (BITMAPFILEHEADER BITMAPINFOHEADER and RGB pixlemap) and the file name
 * 
 * @param File name & BMP struct loaded with data
 * @return Void
 * 
 */
void writeBMP(char *file, BMP *image);

#endif
