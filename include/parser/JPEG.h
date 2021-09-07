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
 * @file JPEG.h
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This file contains JPEG related data types and function prototypes
 */

#pragma once
#ifndef JPEG_H
#define JPEG_H

#include "util/util.h"

/*
 * JPEGDEFAULTHEADER
 * 
 * This structure contains information about the marker, length, identifier
 * version, unit, density, thumbnail.
 *
 */
typedef struct JPEGDEFAULTHEADER
{
    u16 marker;
    u16 length;
    u8 identifier[5];
    u16 version;
    u8 unit;
    u32 density;
    u16 thumbnail;
} __attribute__((__packed__))
JPEGDEFAULTHEADER;

/*
 * QUANTIZATIONTABLE
 *
 * This structure contains information about the marker, length, destination, table.
 *  
 */
typedef struct QUANTIZATIONTABLE
{
    u16 marker;
    u16 length;
    u8 destination;
} __attribute__((__packed__))
QUANTIZATIONTABLE;

/*
 * STARTOFFRAME
 * 
 * This structure contains information about the marker, length, precision, height, width, components count, components.
 * 
 */
typedef struct STARTOFFRAME
{
    u16 marker;
    u16 length;
    u8 precision;
    u16 height;
    u16 width;
    u8 componentsCount;
    u8 factors[9];
} __attribute__((__packed__))
STARTOFFRAME;

/*
 * HUFFMANTABLE
 * 
 * This structure contains information about the marker, length, class, destination, symbol count, symbols.
 * 
 */
typedef struct HUFFMANTABLE
{
    u16 marker;
    u16 length;
    u8 classdestination;
    u8 symbolCount[16];
} __attribute__((__packed__))
HUFFMANTABLE;

/*
 * STARTOFSCAN
 * 
 * This structure contains information about the marker, length, component count, component data (component count x 2).
 * 
 */
typedef struct STARTOFSCAN
{
    u16 marker;
    u16 length;
    u8 componentCount;
} __attribute__((__packed__))
STARTOFSCAN;

/*
 * JPEG 
 *
 * This structure contains information about the image
 * Start of image, Default header, Quantization x 2, Start of frame, Huffman table x 4, Start of scan, Image data, End of image.
 * 
 */
typedef struct JPEG
{
    u16 SOI;
    JPEGDEFAULTHEADER APPLICATION;
    QUANTIZATIONTABLE QT1;
    u8 *QUANTIZATIONTABLE1;
    QUANTIZATIONTABLE QT2;
    u8 *QUANTIZATIONTABLE2;
    STARTOFFRAME SOF;
    HUFFMANTABLE HT1;
    u8 *HT1Code;
    HUFFMANTABLE HT2;
    u8 *HT2Code;
    HUFFMANTABLE HT3;
    u8 *HT3Code;
    HUFFMANTABLE HT4;
    u8 *HT4Code;
    STARTOFSCAN SOS;
    u8 reserved[3];
    u8 *componentData;
    s64 ECGlength;
    u8 *ECG;
    u16 EOI;
} __attribute__((__packed__))
JPEG;

/*
 * open JPEG
 * 
 * The openJPEG Function returns the JPEG file data loaded in the JPEG structure
 * which contains SOI, JPEGDEFAULTHEADER, QUANTIZATIONTABLE, STARTOFFRAME, HUFFMANTABLE, STARTOFSCAN, ECG, EOI.
 * 
 * @param File name
 * @return JPEG struct
 * 
 */
JPEG *openJPEG(char *file);

/*
 * close JPEG
 *
 * The closeJPEG Function frees the allocated memory for image loaded in the JPEG structure.
 * 
 * @param JPEG struct with loaded data
 * @return Void
 * 
 */
void closeJPEG(JPEG *image);

/*
 * write JPEG
 *
 * The writeJPEG Function creates a new JPEG image file with the arguments
 * a JPEG structure which contains the information about the image (SOI, JPEGDEFAULTHEADER, QUANTIZATIONTABLE, STARTOFFRAME, HUFFMANTABLE, STARTOFSCAN, ECG, EOI) and the file name.
 * 
 * @param File name & JPEG struct with loaded data
 * @return void
 * 
 */
void writeJPEG(char *file, JPEG *image);

#endif
