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
 * @file util.c
 * @author Ishant Ram
 * @date 7th September 2021
 * @brief This file contains the util function prototypes implementation from util.h
 * 
 */

#include "util/util.h"
#include "util/stdc.h"

// Wrap
u8 wrap(s64 value)
{
    // If value is greather than 255 wrap it to 255
    if (value > 255)
    {
        return 255;
    }
    // else if value is less than 0 wrap it to 0
    else if (value < 0)
    {
        return 0;
    };
    // else return the value
    return value;
};

// Get type
u8 getType(char *file)
{
    // Opening the file
    FILE *filePTR = fopen(file, "rb");
    if (filePTR == NULL)
    {
        fprintf(stderr, "Could not open %s\n", file);
        return 0;
    };

    // Reading the first 2 bytes
    u16 word;
    fread(&word, sizeof(u16), 1, filePTR);

    // All possible cases
    switch (word)
    {
        // BITMAP
        case 0x4D42:
            fclose(filePTR);
            return BITMAP;

        // JFIF
        case 0xD8FF:
            fclose(filePTR);
            return JFIF;

        default:
            fclose(filePTR);
            return 0;
    };

    return EXIT_SUCCESS;
};