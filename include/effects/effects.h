/**
 * @file effects.h
 * @author Ishant Ram
 * @date 27th December 2021
 * @brief This file contains the effect for image
 * 
 */

#include "util/IMG.h"
#include "util/util.h"

/**
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

/**
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

/**
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

/**
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

/**
 * Reflect
 *
 * The Reflect function Reflects the image horizontally.
 * 
 * @param Generic image struct with loaded data
 * @return Void
 * 
 */
void reflect(IMG *image);

/**
 * Speia
 *
 * The Sepia function addes the Sepia filter to the image
 * 
 * @param Generic image struct with loaded data
 * @return Void
 * 
 * Adapted from http://leware.net/photo/blogSepia.html
 * 
 */
void sepia(IMG *image);

/**
 * Red
 *
 * The red function sets the red compund of the image to 255
 *
 * @param Generic image struct with loaded data
 * @return void
 */
void red(IMG *image);

/**
 * Green
 *
 * The green function sets the green compund of the image to 255
 *
 * @param Generic image struct with loaded data
 * @return void
 */
void green(IMG *image);

/**
 * Blue
 *
 * The blue function sets the blue compund of the image to 255
 *
 * @param Generic image struct with loaded data
 * @return void
 */
void blue(IMG *image);

/**
 * debug
 *
 * A debug function for debugging
 *
 * @param Generic image struct with loaded data
 * @return void
 */
void debug(IMG *image);
