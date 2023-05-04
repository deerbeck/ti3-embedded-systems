#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


// main application
int main(int argc, char* argv[])
{
    //get Image Data
    uint32_t data_size = getBmpDataSize("HM_cube.bmp"), width = getBmpWidth("HM_cube.bmp"), height = getBmpHeight("HM_cube.bmp");
    printf("Bildgröße: %d\n", data_size);
    printf("Bildbreite: %d\n", width);
    printf("Bildhöhe: %d\n", height);
    // end application successfully

    uint8_t data[width*height*8];

    getBmpData("HM_cube.bmp", data);

    return 0;
}
