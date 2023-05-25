#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


#define FILENAME "HM_admin_gray.bmp"


// main application
int main(int argc, char* argv[])
{

    if(argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    //copy filename from argv[1]
    char filename[sizeof(argv[1])*sizeof(char)];
    strcpy(filename,argv[1]);


    //check file existance
    if (existBmp(filename) == -1) return 2;

    //create new image struct and its corresponding pointer
    Image img;
    Image* pimg = &img;

    //set values of struct to read data from header
    pimg->width = getBmpWidth(filename);
    pimg->height = getBmpHeight(filename);
    pimg->datasize = getBmpDataSize(filename);
    //create pointer of size data to get data
    pimg->data = (uint8_t*) malloc(pimg->datasize);
    getBmpData(filename,pimg->data);

    //print Image Data (only for smaller images)
    printfBMP(pimg);

    printf("%s", filename);


    // end application successfully


    //free allocated storage
    free(pimg->data);
    return 0;
}
