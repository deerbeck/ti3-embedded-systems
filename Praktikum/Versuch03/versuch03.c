#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"


#define FILENAME "HM_admin_gray.bmp"


// main application
int main(int argc, char* argv[])
{

    if(argc != 3)
    {
        printf("Usage: %s <filename> <kernels>\n", argv[0]);
        return -1;
    }
    //copy filename from argv
    char filename[strlen(argv[1])+1];
    strcpy(filename,argv[1]);

    //copy kernel filename from argv
    char kernels[strlen(argv[2])+1];
    strcpy(kernels, argv[2]);


    //check file existance
    if (existBmp(filename) == -1) return 2;
    if (existBmp(kernels) == -1) return 3;

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

    //read in Kernels from provided kernel file
    Kernel* kernel_array = readKrnls(kernels);

int test = sizeof(kernel_array);
    for(int i = 0; i < (test); i++)
    {
        //create new filename which includes _gray
        char new_filename[strlen(filename)+ strlen(kernel_array[i].name) + 40];
        strcpy(new_filename, filename);

        //find . in filename to get pointer to that address
        char* dot_ptr = strchr(new_filename,'.');

        //overwrite everything after . in origin filename using dot_ptr
        if (dot_ptr != NULL)
        {
            //format fileending using sprintf and a buffer string with the kernelname
            char buffer[strlen(kernel_array[i].name)+10];
            sprintf(buffer,"_%s.bmp",(kernel_array[i].name));
            strcpy(dot_ptr, buffer);
        }

        //in case filename does not have .bmp ending (highly unlikely because main fails before)
        else
        {
            //format fileending using sprintf and a buffer string with the kernelname
            char buffer[strlen(kernel_array[i].name)+10];
            sprintf(buffer,"_%s.bmp",kernel_array[i].name);
            strcat(new_filename, buffer);
        }

        //convolut the input picture with current kernel
        conv2D(psrc, pdst, &kernel_array[i]);

        //safe convoluted picture in new bmp with different file ending
        saveBmpGray(new_filename,psrc->width,psrc->height,pdst->data);

    }



//    //create dummy kernel
//    Kernel krnl;
//    Kernel* pkrnl = &krnl;
//
//    //define values of kernel
//    strcpy(pkrnl->name, "Dummy-Kernel");
//    float val_src[] = {0.8, -0.7, 0.6, -0.5, 0.4, 0.3, 0.2, -0.1, 0.0};
//    memcpy(pkrnl->values,val_src, sizeof(val_src)*sizeof(float));
//
//
//
//    //print Image Data (only for smaller images)
//    printfBMP(psrc);
//
//
//    conv2D(psrc,pdst,pkrnl);
//    printf("Destinaton:\n");
//    printfBMP(pdst);
//    printf("%s", filename);

    // end application successfully

    printf("Bilder erfolgreich gefiltert!");
    //free allocated storage
    free(kernel_array);
    free(psrc->data);
    free(pdst->data);
    return 0;
}
