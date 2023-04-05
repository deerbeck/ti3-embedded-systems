#include <stdio.h>
#include "ti_bmp.h"


// main application
int main()
{
//    int32_t width = 200;
//    int32_t height = 100;
//    uint32_t datasize = height * width;
//    uint8_t image[datasize];
//    for (uint32_t i = 0; i < datasize; i++)
//    {
//        image[i] = 234;
//   }
//
//    saveBmpGray("hello.bmp", width, height, image);

    int32_t width = 200;
    int32_t height = 200;
    char* image = genBackgroundImage(width, height, 222);
    drawCircles(image, width, height, 5, 10000, 7);
    saveBmpGray("firstimage.bmp", width, height, image);
// end application successfully
    return 0;
}
