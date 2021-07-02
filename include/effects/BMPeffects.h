#pragma once
#include "parser/BMP.h"
#include "util.h"

// Convert image to grayscale
void grayscale(BMP *image);

// Convert image to sepia
void sepia(BMP *image);

// Reflect image horizontally
void reflect(BMP *image);

// Box Blur the image
void blur(BMP *image);
