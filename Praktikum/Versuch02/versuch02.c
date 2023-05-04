#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


// main application
int main(int argc, char* argv[])
{
    char filename[200] = "HM_cube.bmp";

    //get Image Data
    uint32_t data_size = getBmpDataSize(filename), width = getBmpWidth(filename), height = getBmpHeight(filename);
    printf("Datengröße: %d\n", data_size);
    printf("Bildbreite: %d\n", width);
    printf("Bildhöhe: %d\n", height);
    // end application successfully

    uint8_t data[data_size];

    getBmpData(filename, data);

    return 0;
}
