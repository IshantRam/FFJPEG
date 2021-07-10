#pragma once
#include "parser/BMP.h"
#include "util/util.h"

// Box Blur the image
void blur(BMP *image);

// Change the brightnes of image
void brightnes(BMP *image, u8 brightneslevel);

// Chage the contrast of image
void contrast(BMP* image, u8 contrastlevel);

// Convert image to grayscale
void grayscale(BMP *image);

// Reflect image horizontally
void reflect(BMP *image);

// Convert image to sepia
void sepia(BMP *image);
