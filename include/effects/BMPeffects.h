#pragma once
#include "parser/BMP.h"
#include "util.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE** image);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE** image);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE** image);

// Blur image
void blur(int height, int width, RGBTRIPLE** image);
