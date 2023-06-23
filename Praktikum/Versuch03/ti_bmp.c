#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"



uint8_t* genBackgroundImage(int32_t width, int32_t height, uint8_t bgcolor)
{
    //get datasize and generate image pointer
    uint64_t datasize = width * height;
    uint8_t* image = (uint8_t*) malloc(sizeof(uint8_t) * datasize);

    //set each value of image array to bgcolor
    for(uint64_t i = 0; i<datasize; i++)
    {
        *(image + i) = bgcolor;
    }
    return image;
}


void drawCircles(uint8_t* image, int32_t width, int32_t height, uint8_t circleCount, uint32_t pointsPerCircle, uint8_t color)
{
    //get center of image M_B_X = M_B[0] and M_B_Y = M_B[1]
    uint64_t M_B[2] = {(width/2), (height/2)};
    //calculate smallest radius of image
    uint64_t s_radius;
    if(width<height) s_radius = width/circleCount;
    else s_radius = ((height/(circleCount+0.5))/2);

    //loop through points and calculate angle
    double angle = 0, x_val = 0, y_val = 0;

    //loop through number of circles to draw each circles
    for(int j = 1; j<(circleCount+1); j++)
    {
        for(int i = 0; i< pointsPerCircle; i++)
        {
            //calculating angle and coordinates step by step to make code more readable
            angle = (i/(float)pointsPerCircle)*2*M_PI;
            x_val = s_radius* j * cos(angle);
            y_val = s_radius* j  * sin(angle);

            //use pointer_calc function to get translation of coordinates
            *(image + pointer_calc((M_B[0] +(uint64_t) x_val),(M_B[1] + (uint64_t) y_val),height)) = color;
        }
    }
}

uint64_t pointer_calc(uint32_t x, uint32_t y, uint32_t height)
{

    uint64_t result;

    //get length of addres through this formula and return it to get access to array
    result = x + (y * height);

    return result;

}


// checks if file exists
int32_t existBmp(char* filename)
{
    //open file that needs to be checked
    FILE* file = fopen(filename, "r");

    //return -1 and print error code when file doesn't exist
    if (file == NULL)
    {
        printf("Datei konnte nicht gefunden bzw. geöffnet werden!\n");
        return -1;
    }
    //close file after file existance was checked
    fclose(file);

    return 0;
}


// determine width of bmp image
int32_t getBmpWidth(char* filename)
{
    //check existance of file
    if (existBmp(filename) != 0)
    {
        return -1;
    }

    //define offset and size given from BMP definition which corresponds to the bmp width:
    int bmp_width_offset = 18, bmp_width_size = 4;
    //declare variable where size should be saved
    uint32_t bmp_width = 0;

    //open file and seek position of needed position
    FILE* file = fopen(filename, "rb");
    fseek(file, bmp_width_offset, SEEK_SET);


    //read data_size on correct position and save it in location of bmp_width
    fread(&bmp_width, bmp_width_size, 1, file);

    //close file after usage
    fclose(file);


    return bmp_width;
}

// determine height of bmp image
int32_t getBmpHeight(char* filename)
{
    //check existance of file
    if (existBmp(filename) != 0)
    {
        return -1;
    }
    //define offset and size given from BMP definition which corresponds to the bmp height:
    int bmp_height_offset = 22, bmp_height_size = 4;
    //declare variable where size should be saved
    uint32_t bmp_height = 0;

    //open file and seek position of needed position
    FILE* file = fopen(filename, "rb");
    fseek(file, bmp_height_offset, SEEK_SET);


    //read data_size on correct position and save it in location of bmp_height
    fread(&bmp_height, bmp_height_size, 1, file);

    //close file after usage
    fclose(file);


    return bmp_height;
}


// determine height of bmp image
uint32_t getBmpDataSize(char* filename)
{
    //check existance of file
    if (existBmp(filename) != 0)
    {
        return -1;
    }
    //define offset and size given from BMP definition which corresponds to the bmp datasize and bfOffBits:
    int data_size_offset = 2, data_size_size = 4, bfOffBits_offset = 10, bfOffBits_size = 4;
    //declare variable where size and Headersize should be saved
    uint32_t data_size = 0,bfOffBits = 0;


    //open file and seek position of data_size
    FILE* file = fopen(filename, "rb");
    fseek(file, data_size_offset, SEEK_SET);

    //read data_size on correct position and save it in location of data_size
    fread(&data_size, data_size_size, 1, file);


    //get size of Header to subtract later on
    fseek(file, bfOffBits_offset, SEEK_SET);
    fread(&bfOffBits, bfOffBits_size, 1, file);

    //close file after usage
    fclose(file);

    //subtract bfOffBits which is the size of the header to only get datablock size
    return data_size - bfOffBits;
}


// conversion of rgb image to gray image
uint8_t* convertRgb2Gray(uint8_t* image, int32_t datasize)
{
//newimage is 1/3 of old image because it only need to be coded with one grayscale instead of Red Green and Blue
    uint8_t* newimage = (uint8_t*) malloc(sizeof(uint8_t) *(datasize));
    uint8_t gray = 0, red = 0, green = 0, blue = 0;

    for (uint64_t i = 0; i < datasize; i ++)
    {
        //getting RGB-Values from each pixel using factor 3 to scale up the size of the RGB picture
        blue = image[i*3];
        green = image[i*3+1];
        red = image[i*3+2];

        //calculating needed gray Value and write in newimage
        gray = 0.299 *red + 0.587*green + 0.114*blue;
        newimage[i] = gray;
    }
    //return newly created image
    return newimage;
}


// get raw data of image
uint8_t getBmpData(char* filename, uint8_t* data)
{
    //check existance of file
    if (existBmp(filename) != 0)
    {
        printf("Datei konnte nicht gefunden bzw. geöffnet werden!\n");
        return -1;
    }

    //define offset and size given from BMP definition which corresponds to the bmp data:
    int bfOffBits_offset = 10, bfOffBits_size = 4;
    //declare variable where size should be saved
    uint32_t bfOffBits = 0, data_size = getBmpDataSize(filename);

    //open file and seek position of needed bfOffBitsposition
    FILE* file = fopen(filename, "rb");
    fseek(file, bfOffBits_offset, SEEK_SET);
    //get start of data and save in bfOffBits
    fread(&bfOffBits, bfOffBits_size, 1, file);


    //seek position of data in file
    fseek(file, bfOffBits, SEEK_SET);

    //read data from bmp
    fread(data, sizeof(uint8_t), data_size, file);

    //close file after usage
    fclose(file);

    return 0;
}

// print pixels of provided img
void printfBMP(Image* img)
{
    //print out width and height of image
    printf("Width: %i   ",img->width);
    printf("Height: %i\n", img->height);

    //loop through image data and print it out on console
    for(int i = img->height-1; i > -1; i--)
    {
        for(int j = 0; j< img->width; j++)
        {
            //start with the last item and get through each row
            printf("%d\t",img->data[i*img->width + j]);
        }
        printf("\n");
    }
}

//convolution of provided img
void conv2D(Image* src, Image* dst, Kernel* krnl)
{
    long pixelvalue;
    //convolution of image from source to destination
    for(int i = src->height-1; i > -1; i--)
    {
        for(int j = 0; j < src->width; j++)
        {
            // first 4 cases to determine border of picture and set border to 0
            //set horizontal border to 0
            if(i==0)
            {
                dst->data[i*src->width + j] = 0;
            }
            else if (i == src->height-1)
            {
                dst->data[i*src->width + j] = 0;
            }
            //set vertical borders to 0
            else if (j == 0)
            {
                dst->data[i*src->width + j] = 0;
            }
            else if (j == src->width-1)
            {
                dst->data[i*src->width + j] = 0;
            }
            //calculate new pixel value with given kernel
            else
            {
                //safe new pixelvalue into buffervariable
                pixelvalue = (int)(src->data[(i+1)*src->width+j-1]*krnl->values[0] + src->data[(i+1)*src->width+j]*krnl->values[1] + src->data[(i+1)*src->width+j+1]*krnl->values[2] + src->data[(i)*src->width+j-1]*krnl->values[3] + src->data[(i)*src->width+j]*krnl->values[4] + src->data[(i)*src->width+j+1]*krnl->values[5] + src->data[(i-1)*src->width+j-1]*krnl->values[6] + src->data[(i-1)*src->width+j]*krnl->values[7] + src->data[(i-1)*src->width+j+1]*krnl->values[8]);
                //check boundaries of allowed pixelvalue
                if (pixelvalue < 0) pixelvalue = 0;
                else if (pixelvalue > 255) pixelvalue = 255;
                //safe new pixelvalue into data
                dst->data[i*src->width + j] = (uint8_t) pixelvalue;

            }
        }
    }
}

//read kernels from provided file
Kernel* readKrnls(char* filename)
{
    //read in file and initialize varibales
    FILE* file = fopen(filename, "r");
    char buffer[200];
    int lines = 0;
    char c;

    //loop through lines to get nunber of kernels
    while((c = fgetc(file)) != EOF)
    {
        if (c == '\n') lines++;
    }

    //reset file courser to start of file
    fseek(file,0,0);

    //allocate memory for the kernelarray
    Kernel* kernel_array = (Kernel*) malloc(lines*sizeof(Kernel));

    //read out kernel data from txt file
    int line = 0;
    while(fgets(buffer,sizeof(buffer), file) != NULL)
    {
        //use sscanf f to read out formated string from line
        sscanf(buffer,"%s %f %f %f %f %f %f %f %f %f\r\n", kernel_array[line].name, &kernel_array[line].values[0], &kernel_array[line].values[1], &kernel_array[line].values[2],&kernel_array[line].values[3], &kernel_array[line].values[4],&kernel_array[line].values[5],&kernel_array[line].values[6],&kernel_array[line].values[7],&kernel_array[line].values[8]);
        line++;
    }


    //close file and return array
    fclose(file);
    return kernel_array;
}

uint8_t saveBmpGray(char* filename, int32_t width, int32_t height, uint8_t* data)
{
    int ret = 0;

    // management variables for bmp file format
    uint8_t header[54] = {0};
    uint32_t* p32 = NULL;
    uint16_t* p16 = NULL;
    uint32_t datawidth = ((width + 3) / 4) * 4;
    uint32_t datasize = datawidth * height;

    // bmp file header
    p16 = (uint16_t*)(header + 0);
    *p16 = 0x4D42;
    p32 = (uint32_t*)(header + 2);
    *p32 = 14 + 40 + 256 * 4 + datasize;
    p32 = (uint32_t*)(header + 10);
    *p32 = 14 + 40 + 256 * 4;

    // bmp info header
    p32 = (uint32_t*)(header + 14);
    *p32 = 40;
    p32 = (uint32_t*)(header + 18);
    *p32 = width;
    p32 = (uint32_t*)(header + 22);
    *p32 = height;
    p16 = (uint16_t*)(header + 26);
    *p16 = 1;
    p16 = (uint16_t*)(header + 28);
    *p16 = 8;
    p32 = (uint32_t*)(header + 30);
    *p32 = 0;
    p32 = (uint32_t*)(header + 34);
    *p32 = datasize;

    // bmp color information
    uint8_t colors[256 * 4] = {0};
    for (int i = 0; i < 256; i++)
        colors[i * 4 + 0] = colors[i * 4 + 1] = colors[i * 4 + 2] = i;

    // bmp file saving
    FILE* fp = NULL;
    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        // end function indicating error by -1
        ret = -1;
    }
    else
    {
        // write header and color information
        fwrite(header, sizeof(uint8_t), 54, fp);
        fwrite(colors, sizeof(uint8_t), 256 * 4, fp);

        // bmp needs width with multiple of 4
        // padding bytes fill up possible missing bytes (multiple of 4)
        uint8_t padding = datawidth - width;
        for(int i = 0; i < height; i++)
        {
            // image data
            fwrite(data+i*width, sizeof(uint8_t), width, fp);
            // padding bytes
            if ( padding != 0 )
            {
                // if padding is needed it is 1-3 bytes
                // uint32_t holds 4 bytes of 0s
                // static variable for single initialization
                static uint32_t paddingBytes = 0;
                fwrite(&paddingBytes, sizeof(uint8_t), padding, fp);
            }
        }

        fclose(fp);
    }

    return ret;
}


