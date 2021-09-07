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
 * @file effects.h
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This file contains the effect for image
 * 
 */

#pragma once
#include "util/IMG.h"
#include "parser/BMP.h"
#include "util/util.h"

/*
 * Blur
 *
 * The Blur function Box blurs the image.
 * 
 * @param Generic image struct with loaded data
 * @return Void
 * 
 * Adapted from https://en.wikipedia.org/wiki/Box_blur#Implementation
 * 
 */
void blur(IMG *image);

/*
 * Brightness
 * 
 * The brigthness fuction changes the brightness of image according to given level.
 * 
 * @param Generic image struct with loaded data
 * @param Brightness level
 * @return Void
 *
 * Adapted from https://ie.nitk.ac.in/blog/2020/01/19/algorithms-for-adjusting-brightness-and-contrast-of-an-image/
 * 
 */
void brightnes(IMG *image, u8 brightneslevel);

/*
 * Contrast
 * 
 * The Contrast fuction changes the Contrast of image according to given level.
 * 
 * @param Generic image struct with loaded data
 * @param Contrast level
 * @return Void
 *
 * Adapted from https://ie.nitk.ac.in/blog/2020/01/19/algorithms-for-adjusting-brightness-and-contrast-of-an-image/
 * 
 */
void contrast(IMG *image, u8 contrastlevel);

/*
 * Grayscale
 *
 * The Grayscale function Grayscales the image.
 * 
 * @param Generic image struct with loaded data
 * @return Void
 * 
 * Adapted from https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
 * 
 */
void grayscale(IMG *image);

/*
 * Reflect
 *
 * The Reflect function Reflects the image horizontally.
 * 
 * @param Generic image struct with loaded data
 * @return Void
 * 
 */
void reflect(IMG *image);

/* 
 * Reflect
 *
 * The Reflect function Reflects the image horizontally.
 * 
 * @param Generic image struct with loaded data
 * @return Void
 * 
 * Adapted from http://leware.net/photo/blogSepia.html
 * 
 */
void sepia(IMG *image);
