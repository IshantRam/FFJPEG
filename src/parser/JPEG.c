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

#include "util/stdc.h"
#include "parser/JPEG.h"

// Open JPEG
JPEG *openJPEG(char *file)
{
    // Opening the file in read byte mode
    FILE *filePTR = fopen(file, "rb");
    if (filePTR == NULL)
    {
        fprintf(stderr, "Could not open %s\n", file);
        return NULL;
    };

    // Allocating memory for image
    JPEG *image = malloc(sizeof(JPEG));
    if (image == NULL)
    {
        fclose(filePTR);
        return NULL;
    };

    // Ensure file is JPEG
    fread(&image->SOI, sizeof(u16), 1, filePTR);
    if (image->SOI != 0xD8FF)
    {
        fprintf(stderr, "%s is not a JPEG image\n", file);
        fclose(filePTR);
        return NULL;
    };

    // Read files JPEGDEFAULTHEADER
    fread(&image->APPLICATION, sizeof(JPEGDEFAULTHEADER), 1, filePTR);

    // Read files QUANTIZATIONTABLE
    fread(&image->QT1, sizeof(QUANTIZATIONTABLE), 1, filePTR);
    image->QUANTIZATIONTABLE1 = malloc(sizeof(u8) * (image->QT1.length >> 8) - 3);
    if (image->QUANTIZATIONTABLE1 == NULL)
    {
        return NULL;
    };
    fread(image->QUANTIZATIONTABLE1, sizeof(u8) * (image->QT1.length >> 8) - 3, 1, filePTR);

    fread(&image->QT2, sizeof(QUANTIZATIONTABLE), 1, filePTR);
    image->QUANTIZATIONTABLE2 = malloc(sizeof(u8) * (image->QT2.length >> 8) - 3);
    if (image->QUANTIZATIONTABLE2 == NULL)
    {
        return NULL;
    };
    fread(image->QUANTIZATIONTABLE2, sizeof(u8) * (image->QT2.length >> 8) - 3, 1, filePTR);

    // Read files STARTOFFRAME
    fread(&image->SOF, sizeof(STARTOFFRAME), 1, filePTR);

    // Read files HUFFMANTABLE
    fread(&image->HT1, sizeof(HUFFMANTABLE), 1, filePTR);
    image->HT1Code = malloc(sizeof(u8) * (image->HT1.length >> 8) - 19);
    if (image->HT1Code == NULL)
    {
        return NULL;
    };
    fread(image->HT1Code, sizeof(u8) * (image->HT1.length >> 8) - 19, 1, filePTR);

    fread(&image->HT2, sizeof(HUFFMANTABLE), 1, filePTR);
    image->HT2Code = malloc(sizeof(u8) * (image->HT2.length >> 8) - 19);
    if (image->HT2Code == NULL)
    {
        return NULL;
    };
    fread(image->HT2Code, sizeof(u8) * (image->HT2.length >> 8) - 19, 1, filePTR);

    fread(&image->HT3, sizeof(HUFFMANTABLE), 1, filePTR);
    image->HT3Code = malloc(sizeof(u8) * (image->HT3.length >> 8) - 19);
    if (image->HT3Code == NULL)
    {
        return NULL;
    };
    fread(image->HT3Code, sizeof(u8) * (image->HT3.length >> 8) - 19, 1, filePTR);

    fread(&image->HT4, sizeof(HUFFMANTABLE), 1, filePTR);
    image->HT4Code = malloc(sizeof(u8) * (image->HT4.length >> 8) - 19);
    if (image->HT4Code == NULL)
    {
        return NULL;
    };
    fread(image->HT4Code, sizeof(u8) * (image->HT4.length >> 8) - 19, 1, filePTR);

    // Read files STARTOFSCAN
    fread(&image->SOS, sizeof(STARTOFSCAN), 1, filePTR);
    image->componentData = malloc(sizeof(u8) * (image->SOS.componentCount * 2));
    if (image->componentData == NULL)
    {
        return NULL;
    };
    fread(image->componentData, sizeof(u8) * (image->SOS.componentCount * 2), 1, filePTR);
    fread(image->reserved, sizeof(u8) * 3, 1, filePTR);

    // Read files ENTROPY CODED SEGMENT
    s64 offset = ftell(filePTR);
    fseek(filePTR, -2, SEEK_END);
    image->ECGlength = ftell(filePTR) - offset;
    rewind(filePTR);
    fseek(filePTR, offset, SEEK_CUR);
    image->ECG = malloc(image->ECGlength);
    fread(image->ECG, image->ECGlength, 1, filePTR);

    // Read files EOI
    fread(&image->EOI, sizeof(u16), 1, filePTR);

    // Closing the file pointer
    fclose(filePTR);

    return image;
};

// Close JPEG
void closeJPEG(JPEG *image)
{
    // if image is invalid
    if (image == NULL)
    {
        fprintf(stderr, "Invalid image\n");
        return;
    };

    // Free QUANTIZATIONTABLEs
    free(image->QUANTIZATIONTABLE1);
    free(image->QUANTIZATIONTABLE2);

    // Free HUFFMANTABLEs
    free(image->HT1Code);
    free(image->HT2Code);
    free(image->HT3Code);
    free(image->HT4Code);

    // Free STARTOFSCAN component data
    free(image->componentData);

    // Free ECG
    free(image->ECG);

    // Free the image
    free(image);

    return;
};

// Write JPEG
void writeJPEG(char *file, JPEG *image)
{
    // Opening the file in write byte mode
    FILE *filePTR = fopen(file, "wb");
    if (filePTR == NULL)
    {
        fprintf(stderr, "Could not open %s\n", file);
        return;
    };

    // Write the SOI
    fwrite(&image->SOI, sizeof(u16), 1, filePTR);

    // Write the JPEGDEFAULTHEADER
    fwrite(&image->APPLICATION, sizeof(JPEGDEFAULTHEADER), 1, filePTR);

    // Write the QUANTIZATIONTABLE
    fwrite(&image->QT1, sizeof(QUANTIZATIONTABLE), 1, filePTR);
    fwrite(image->QUANTIZATIONTABLE1, sizeof(u8) * (image->QT1.length >> 8) - 3, 1, filePTR);

    fwrite(&image->QT2, sizeof(QUANTIZATIONTABLE), 1, filePTR);
    fwrite(image->QUANTIZATIONTABLE2, sizeof(u8) * (image->QT2.length >> 8) - 3, 1, filePTR);

    // Write the STARTOFFRAME
    fwrite(&image->SOF, sizeof(STARTOFFRAME), 1, filePTR);

    // Write the HUFFMANTABLE
    fwrite(&image->HT1, sizeof(HUFFMANTABLE), 1, filePTR);
    fwrite(image->HT1Code, sizeof(u8) * (image->HT1.length >> 8) - 19, 1, filePTR);

    fwrite(&image->HT2, sizeof(HUFFMANTABLE), 1, filePTR);
    fwrite(image->HT2Code, sizeof(u8) * (image->HT2.length >> 8) - 19, 1, filePTR);

    fwrite(&image->HT3, sizeof(HUFFMANTABLE), 1, filePTR);
    fwrite(image->HT3Code, sizeof(u8) * (image->HT3.length >> 8) - 19, 1, filePTR);

    fwrite(&image->HT4, sizeof(HUFFMANTABLE), 1, filePTR);
    fwrite(image->HT4Code, sizeof(u8) * (image->HT4.length >> 8) - 19, 1, filePTR);

    // Write the STARTOFSCAN
    fwrite(&image->SOS, sizeof(STARTOFSCAN), 1, filePTR);
    fwrite(image->componentData, sizeof(u8) * (image->SOS.componentCount * 2), 1, filePTR);
    fwrite(image->reserved, sizeof(u8) * 3, 1, filePTR);

    // Write files ENTROPY CODED SEGMENT
    fwrite(image->ECG, image->ECGlength, 1, filePTR);
    
    // Write files EOI
    fwrite(&image->EOI, sizeof(u16), 1, filePTR);

    // Closing the file
    fclose(filePTR);

    return;
};