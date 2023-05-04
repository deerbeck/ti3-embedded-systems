#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


// main application
int main(int argc, char* argv[])
{
    char filename[200] = "test/codeblocks1.bmp";

    //get Image Properties
    uint32_t data_size = getBmpDataSize(filename), width = getBmpWidth(filename), height = getBmpHeight(filename);
    printf("Datengröße: %d\n", data_size);
    printf("Bildbreite: %d\n", width);
    printf("Bildhöhe: %d\n", height);
    // end application successfully

    //get image data
    uint8_t data[data_size];
    getBmpData(filename, data);

    //convert colorimage to grayscaleimage
    uint8_t *image = convertRgb2Gray(data, data_size/3);

    //safe converted image and freeup allocated space
    saveBmpGray("Test2.bmp", width, height , image);
    free(image);
    return 0;
}
