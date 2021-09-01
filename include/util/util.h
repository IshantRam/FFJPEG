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

#pragma once
#ifndef UTIL_H
#define UTIL_H

/*
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

/*
 * RGB
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 * 
 */
typedef struct RGB
{
	u8 red;
	u8 green;
	u8 blue;
} __attribute__((__packed__))
RGB;

/* 
 * Wrap
 *
 * if the give value is greather than 255 it wrpas it up to 255, if less than 0 wraps it up to 0 .
 * 
 */
u8 wrap(s64 value);

/*
 * get Type
 *
 * The get type function gets the image type.
 * 
 */
u8 getType(char *file);

#endif