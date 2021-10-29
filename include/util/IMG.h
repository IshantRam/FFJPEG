/**
 * @file IMG.h
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This files contains the data types and function prototypes for Generic image struct.
 * 
 */

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

/**
 * BMP to IMG
 *
 * The BMP to IMG function converts the BMP image loaded in the BMP struct to IMG struct image.
 * 
 * @param BMP struct loaded with data
 * @return IMG struct
 * 
 */
IMG *BMPtoIMG(BMP *image);

/**
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

/**
 * Close IMG
 * 
 * The closeIMG Function frees the allocated memory for image loaded in the IMG structure
 * 
 * @param IMG struct loaded with data
 * 
 */
void closeIMG(IMG *image);

#endif