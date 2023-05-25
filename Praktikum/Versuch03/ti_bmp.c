#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"



uint8_t* genBackgroundImage(int32_t width, int32_t height, uint8_t bgcolor)
{
    // TODO: Lösung aus Versuch 1 kopieren
    return NULL;
}

void drawCircles(uint8_t* image, int32_t width, int32_t height, uint8_t circleCount, uint32_t pointsPerCircle, uint8_t color)
{
    // TODO: Lösung aus Versuch 1 kopieren
}

// checks if file exists
int32_t existBmp(char* filename)
{
    // TODO: Lösung aus Versuch 2 kopieren
    return 42;
}

// determine width of bmp image
int32_t getBmpWidth(char* filename)
{
    // TODO: Lösung aus Versuch 2 kopieren
    return 42;
}

// determine height of bmp image
int32_t getBmpHeight(char* filename)
{
    // TODO: Lösung aus Versuch 2 kopieren
    return 42;
}

// determine height of bmp image
uint32_t getBmpDataSize(char* filename)
{
    // TODO: Lösung aus Versuch 2 kopieren
    return 42;
}

// conversion of rgb image to gray image
uint8_t* convertRgb2Gray(uint8_t* image, int32_t datasize)
{
    // TODO: Lösung aus Versuch 2 kopieren
    return NULL;
}

// get raw data of image
uint8_t getBmpData(char* filename, uint8_t* data)
{
    // TODO: Lösung aus Versuch 2 kopieren
    return 42;
}

void printfBMP(Image* img)
{
    // TODO:
}

void conv2D(Image* src, Image* dst, Kernel* krnl)
{
    // TODO:
}

uint8_t saveBmpGray(char* filename, int32_t width, int32_t height, uint8_t* data)
{
    int ret = 0;

    // management variables for bmp file format
    uint8_t header[54] = {0};
    uint32_t* p32 = NULL;
    uint16_t* p16 = NULL;
    uint32_t datawidth = ((width + 3) / 4) * 4;
    uint32_t datasize = datawidth * height;

    // bmp file header
    p16 = (uint16_t*)(header + 0);
    *p16 = 0x4D42;
    p32 = (uint32_t*)(header + 2);
    *p32 = 14 + 40 + 256 * 4 + datasize;
    p32 = (uint32_t*)(header + 10);
    *p32 = 14 + 40 + 256 * 4;

    // bmp info header
    p32 = (uint32_t*)(header + 14);
    *p32 = 40;
    p32 = (uint32_t*)(header + 18);
    *p32 = width;
    p32 = (uint32_t*)(header + 22);
    *p32 = height;
    p16 = (uint16_t*)(header + 26);
    *p16 = 1;
    p16 = (uint16_t*)(header + 28);
    *p16 = 8;
    p32 = (uint32_t*)(header + 30);
    *p32 = 0;
    p32 = (uint32_t*)(header + 34);
    *p32 = datasize;

    // bmp color information
    uint8_t colors[256 * 4] = {0};
    for (int i = 0; i < 256; i++)
        colors[i * 4 + 0] = colors[i * 4 + 1] = colors[i * 4 + 2] = i;

    // bmp file saving
    FILE* fp = NULL;
    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        // end function indicating error by -1
        ret = -1;
    }
    else
    {
        // write header and color information
        fwrite(header, sizeof(uint8_t), 54, fp);
        fwrite(colors, sizeof(uint8_t), 256 * 4, fp);

        // bmp needs width with multiple of 4
        // padding bytes fill up possible missing bytes (multiple of 4)
        uint8_t padding = datawidth - width;
        for(int i = 0; i < height; i++)
        {
            // image data
            fwrite(data+i*width, sizeof(uint8_t), width, fp);
            // padding bytes
            if ( padding != 0 )
            {
                // if padding is needed it is 1-3 bytes
                // uint32_t holds 4 bytes of 0s
                // static variable for single initialization
                static uint32_t paddingBytes = 0;
                fwrite(&paddingBytes, sizeof(uint8_t), padding, fp);
            }
        }

        fclose(fp);
    }

    return ret;
}


