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

/*
 * @file IMG.h
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This files contains the data types and function prototypes for Generic image struct.
 * 
 */

#pragma once
#ifndef IMG_H
#define IMG_H

#include "util/util.h"
#include "parser/BMP.h"

/*
 * IMG
 *
 * This structure describes the basic image data which contains 
 * height, width and RGB image data, this struct is used as genreic image struct in FFJPEG.
 * 
 */
typedef struct IMG
{
	s64 width;
	s64 height;
	RGB **pixlemap;
} __attribute__((__packed__))
IMG;

/*
 * BMP to IMG
 *
 * The BMP to IMG function converts the BMP image loaded in the BMP struct to IMG struct image.
 * 
 * @param BMP struct loaded with data
 * @return IMG struct
 * 
 */
IMG *BMPtoIMG(BMP *image);

/*
 * IMG to BMP
 *
 * The IMG to BMP function converts the image loaded in the IMG struct to BMP struct image.
 * 
 * @param IMG struct loaded with data
 * @param BMP struct loaded with data
 * @return BMP struct
 * 
 */
BMP *IMGtoBMP(IMG *image, BMP *BMPimage);

/*
 * Close IMG
 * 
 * The closeIMG Function frees the allocated memory for image loaded in the IMG structure
 * 
 * @param IMG struct loaded with data
 * 
 */
void closeIMG(IMG *image);

#endif