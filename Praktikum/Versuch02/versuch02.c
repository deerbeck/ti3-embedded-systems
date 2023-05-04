#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


// main application
int main(int argc, char* argv[])
{

    printf("Bildgröße: %d\n", getBmpDataSize("HM_cube.bmp"));
    printf("Bildbreite: %d\n", getBmpWidth("HM_cube.bmp"));
    printf("Bildhöhe: %d\n", getBmpHeight("HM_cube.bmp"));
    // end application successfully
    return 0;
}
