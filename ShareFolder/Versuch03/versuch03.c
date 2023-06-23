#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"

#define INPUT_KERNEL "kernels.txt"

#define FILENAME "HM_admin_gray.bmp"



// main application
int main(int argc, char* argv[])
{

    //needed variables
    char buffer[200];
    uint8_t lines = 0;
    char c;


    //Read out the kernel data


    //check if file exists
    if (existBmp(INPUT_KERNEL) ==  -1) return 3;

    //open the text file
    FILE* file;
    file = fopen(INPUT_KERNEL,"r");

    //checking out many lines you need for the creation of the kernel array
    //fgetc function like in skript

    while(( c = fgetc(file)) != EOF)
    {

        //each new kernel starts with a new line
        if (c == '\n')
        {
            lines++;
        }
    }

    //with that information, you can create the kernelarray
    Kernel*  kernelarray = (Kernel*) malloc((lines + 1) * sizeof(Kernel));
    Kernel* kernel_array = kernelarray;
    //now go back to the beginning of the file and read out the data
    fseek(file,0,0);

    //gets data in buffer
    while(fgets(buffer,sizeof(buffer),file) != NULL)
    {

        //at first san name

        int line = 0;
        while(fgets(buffer,sizeof(buffer), file) != NULL)
        {
            sscanf(buffer,"%s %f %f %f %f %f %f %f %f %f\r\n", kernel_array[line].name, &kernel_array[line].values[0], &kernel_array[line].values[1], &kernel_array[line].values[2],&kernel_array[line].values[3], &kernel_array[line].values[4],&kernel_array[line].values[5],&kernel_array[line].values[6],&kernel_array[line].values[7],&kernel_array[line].values[8]);
            line++;
        }
    }





//file schliesen
fclose(file);




//checken ob file gefunden wird
if(existBmp(argv[1]) == -1) return 3;

//create a test structure for the functions

//create the image-structures
Image original_image, kernel_image;
Image * p_original_image = &original_image;
Image * p_kernel_image = &kernel_image;

//create space for the image data
// uint8_t* original_data = (uint8_t*) malloc(getBmpDataSize("test.bmp"));
// uint8_t* kernel_data = (uint8_t*) malloc( getBmpDataSize("test.bmp"));

//original image inizialise
p_original_image->datasize = getBmpDataSize((argv[1]);
p_original_image->height = getBmpHeight(argv[1]);
p_original_image->width = getBmpWidth((argv[1]);
p_original_image->data = (uint8_t*) malloc(p_original_image->datasize);

//write testpicture in original_image data
if(getBmpData("test.bmp",p_original_image->data) == -1) return 1;

//kernal image inizialise
p_kernel_image->datasize = getBmpDataSize("test.bmp");
p_kernel_image->height = getBmpHeight("test.bmp");
p_kernel_image->width = getBmpWidth("test.bmp");
p_kernel_image->data = (uint8_t*) malloc(p_kernel_image->datasize);


//create the kernel test structure
Kernel dummy;
Kernel * p_dummy = &dummy;

//values of the testkernel
float var[] = {0.8,-0.7,0.6,-0.5,0.4,0.3,0.2,-0.1,0.0};

//inizialize the dummy
memcpy(p_dummy->values,var,sizeof(var));

//for (uint8_t i = 0; i<8; i++) *(p_dummy->values+i) = *(var + i);
//for (uint8_t i = 0; i<8; i++) printf("%f   " , *(dummy.values + i));

//change the test picture with the kernel
conv2D(p_original_image,p_kernel_image, &kernelarray[3]);

//print the image with the print image function
printfBMP(p_original_image);

//print the dummy image
printfBMP(p_kernel_image);

//free the data from image if not need anymore
free(p_original_image->data);
free(p_kernel_image->data);
//    free(kernelarray);

// end application successfully
return 0;

}
