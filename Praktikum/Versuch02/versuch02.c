#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


// main application
int main(int argc, char* argv[])
{
    //cover wrong commandinput
    if (argc != 2)
    {
        printf("Usage: %s <RGB_file>\n", argv[0]);
        return 1;
    }
    //check file existance
    char filename[200];
    strcpy(filename, argv[1]);
    if (existBmp(filename) == -1) return 2;

    //create new filename which includes _gray
    char new_filename[200];
    strcpy(new_filename, filename);

    //find . in filename to get pointer to that address
    char* dot_ptr = strchr(new_filename,'.');

    //overwrite everything after . in origin filename using dot_ptr
    if (dot_ptr != NULL)
    {
        strcpy(dot_ptr, "_gray.bmp");
    }

    //in case filename does not have .bmp ending (highly unlikely because main fails before)
    else
    {
        strcat(new_filename, "_gray.bmp");
    }



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
    saveBmpGray(new_filename, width, height, image);
    free(image);
    return 0;
}
