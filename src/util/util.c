/**
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
    return (u8)value;
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

    // Closing the file pointer
    fclose(filePTR);

    // All supported image formats by FFJPEG
    switch (word)
    {
        // BITMAP
        case 0x4D42:
            return BITMAP;

        // JFIF
        case 0xD8FF:
            return JFIF;

        default:
            return 0;
    };

    return EXIT_SUCCESS;
};