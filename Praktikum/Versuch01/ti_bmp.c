#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"



uint8_t* genBackgroundImage(int32_t width, int32_t height, uint8_t bgcolor)
{
    //get datasize and generate image pointer
    uint64_t datasize = width * height;
    uint8_t* image = (uint8_t*) malloc(sizeof(uint8_t) * datasize);

    //set each value of image array to bgcolor
    for(uint64_t i = 0; i<datasize; i++)
    {
        *(image + i) = bgcolor;
    }
    return image;
}

void drawCircles(uint8_t* image, int32_t width, int32_t height, uint8_t circleCount, uint32_t pointsPerCircle, uint8_t color)
{
    //get center of image M_B_X = M_B[0] and M_B_Y = M_B[1]
    uint64_t M_B[2] = {(width/2), (height/2)};
    //calculate smallest radius of image
    uint64_t s_radius;
    if(width<height) s_radius = width/circleCount;
    else s_radius = ((height/(circleCount+0.5))/2);

    //loop through points and calculate angle
    double angle = 0, x_val = 0, y_val = 0;

    //loop through number of circles to draw each circles
    for(int j = 1; j<(circleCount+1); j++)
    {
        for(int i = 0; i< pointsPerCircle; i++)
        {
            //calculating angle and coordinates step by step to make code more readable
            angle = (i/(float)pointsPerCircle)*2*M_PI;
            x_val = s_radius* j * cos(angle);
            y_val = s_radius* j  * sin(angle);

            //use pointer_calc function to get translation of coordinates
            *(image + pointer_calc((M_B[0] +(uint64_t) x_val),(M_B[1] + (uint64_t) y_val),height)) = 0;
        }
    }

    *(image + pointer_calc(M_B[0],M_B[1],height)) = 0;
}

uint64_t pointer_calc(uint32_t x, uint32_t y, uint32_t height)
{

    uint64_t result;

    //get length of addres through this formula and return it to get access to array
    result = x + (y * height);

    return result;

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
