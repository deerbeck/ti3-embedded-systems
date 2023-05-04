#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


// main application
int main(int argc, char* argv[])
{
    //get Image Data
    uint32_t data_size = getBmpDataSize("codeblocks1.bmp"), width = getBmpWidth("codeblocks1.bmp"), height = getBmpHeight("codeblocks1.bmp");
    printf("Datengröße: %d\n", data_size);
    printf("Bildbreite: %d\n", width);
    printf("Bildhöhe: %d\n", height);
    // end application successfully

    uint8_t data[data_size];

    getBmpData("codeblocks1.bmp", data);

    return 0;
}
