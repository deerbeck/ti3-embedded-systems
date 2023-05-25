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
    Image src,dst;
    Image* psrc = &src;
    Image* pdst = &dst;

    //set values of src image with data from helper functions
    psrc->width = getBmpWidth(filename);
    psrc->height = getBmpHeight(filename);
    psrc->datasize = getBmpDataSize(filename);
    //create pointer of size data to get data
    psrc->data = (uint8_t*) malloc(psrc->datasize);
    getBmpData(filename,psrc->data);

    //create destination image struct with same key data as source image
    pdst->width = psrc->width;
    pdst->height = psrc->height;
    pdst->datasize = psrc->datasize;
    pdst->data = (uint8_t*) malloc(pdst->datasize);

    //create dummy kernel
    Kernel krnl;
    Kernel* pkrnl = &krnl;

    //define values of kernel
    strcpy(pkrnl->name, "Dummy-Kernel");
    float val_src[] = {0.8, -0.7 , 0.6 , -0.5 , 0.4 , 0.3 , 0.2 , -0.1 , 0.0};
    memcpy(pkrnl->values,val_src, sizeof(val_src)*sizeof(float));



    //print Image Data (only for smaller images)
    printfBMP(psrc);


    conv2D(psrc,pdst,pkrnl);
    printf("Destinaton:\n");
    printfBMP(pdst);
    printf("%s", filename);

    // end application successfully


    //free allocated storage
    free(psrc->data);
    free(pdst->data);
    return 0;
}
