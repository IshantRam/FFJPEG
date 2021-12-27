/**
 * @file util.h
 * @author Ishant Ram
 * @date 27th December 2021
 * @brief This files contains util data types and function prototypes.
 * 
 */
#ifndef UTIL_H
#define UTIL_H

/*
 *
 * Image type macros
 *
 */
#define BITMAP 1
#define JFIF 2

/*
 * Common Data Types
 *
 * The data types in this section are essentially aliases for C/C++
 * primitive data types.
 * 
 * See http://en.wikipedia.org/wiki/Stdint.h for more info.
 *
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;

/*
 * RGB
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 * 
 */
typedef struct RGB
{
	u8 R;
	u8 G;
	u8 B;
} __attribute__((__packed__))
RGB;

/*
 * YCbCr
 *
 * This structure describes a color consisting of relative intensities of
 * luma, chroma blue, chroma red.
 * 
 */
typedef struct YCbCr
{
	u8 Y;
	u8 Cb;
	u8 Cr;
} __attribute__((__packed__))
YCbCr;

/**
 * RGB to YCbCr
 * 
 * This function converts a YCbCr pixel to an RGB pixel.
 * 
 * @param pixel 
 * @return YCbCr 
 */
YCbCr RGBtoYCbCr(RGB pixel);

/** 
 * Wrap
 *
 * if the give value is greather than 255 it wrpas it up to 255, if less than 0 wraps it up to 0 .
 * 
 * @param N
 * @return Wrapped value
 * 
 */
u8 wrap(s64 value);

/**
 * get Type
 *
 * The get type function gets the image type.
 * 
 * @param File name
 * @return Type of image mapped with number according to Image type macros
 * 
 */
u8 getType(char *file);

#endif
