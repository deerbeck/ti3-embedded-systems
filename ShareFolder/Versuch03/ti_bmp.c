#include <stdio.h>
#include <string.h>
#include "ti_bmp.h"



uint8_t* genBackgroundImage(int32_t width, int32_t height, uint8_t bgcolor)
{
    {
        //creating a variable for the size of the immage
        uint64_t datasize = width * height;
        uint8_t* image = (uint8_t*) malloc(sizeof(uint8_t) * datasize);

        //memset als alternative
        for(uint64_t i = 0; i<datasize; i++)
        {
            image[i] = bgcolor;
        }


        return image;
    }

}

void drawCircles(uint8_t* image, int32_t width, int32_t height, uint8_t circleCount, uint32_t pointsPerCircle, uint8_t color)
{
//calculation of the radius r of the smallest circle by leaving distance to the edge and divide the space into the count of circles
    uint16_t r = (width / 2 - 10) / circleCount;

//Loop in which the radii are calculated and the several circles are drawn
    for (uint8_t j = 1; j <= circleCount; j++ )
    {
        //Loop, which devided a circle into the number of pieces,, the variable pointsPerCircle gives you
        //a represents the angle of the circle
        for(uint32_t i = 0; i < pointsPerCircle; i++)
        {

            //calculation of the angle of image point
            double angle = (i/(double)pointsPerCircle) * 2 *M_PI;

            //calculate coordinates the centered coordinate system
            int x_cod_centred = r * j * cos(angle);
            int y_cod_centred = r * j * sin(angle);
            //calculate the coordinates of the original system
            uint64_t x_cod_origional = (width / 2) + x_cod_centred;
            uint64_t y_cod_origional = (height / 2) - y_cod_centred;

            //creating the Pixel-Number out of the original coordinates
            uint64_t number = x_cod_origional + y_cod_origional * width;

            //pointer, which goes to the picture and draws the imagePoint in the color in order to create a circle
            *(image + number) = color;
        }
    }
}


// checks if file exists
int32_t existBmp(char* filename)
{
    // declare Var for File
    FILE* file;

    //Open file
    file = fopen(filename, "r");

    //check if file exists
    if (file == NULL)
    {


        //file was not found
        printf("Datei konnte nicht gefunden werden!\n");
        return -1;
    }
    else
    {

        //close file
        fclose(file);
        //file was found
        return 0;
    }
}


// determine width of bmp image
int32_t getBmpWidth(char* filename)
{

    //check if file can be found
    if(existBmp(filename) == -1) return -1;

    //var for width of image
    int32_t width;

    //open file
    FILE* file;
    file = fopen(filename, "rb");

    //set position of file
    fseek(file, 18, SEEK_SET);

    //reading out the data
    if (fread(&width,sizeof(int32_t),1,file) == 0)
    {
        //only jumpes in this if section if it could not be read
        printf("Failure! Data could not be read!\n");

        //close file
        fclose(file);

        return -1;
    }
    //close file
    fclose(file);


    //return width
    return width;

}


// determine height of bmp image
int32_t getBmpHeight(char* filename)
{
    //var for width of image
    int32_t height;

    //check if file can be found
    if(existBmp(filename) == -1) return -1;

    //open file
    FILE* file;
    file = fopen(filename, "rb");

    //set position of file
    fseek(file, 22, SEEK_SET);

    //reading out the data
    if (fread(&height,sizeof(int32_t),1,file) == 0)
    {
        //only jumpes in this if section if it could not be read
        printf("Failure! Data could not be read!\n");

        //close file
        fclose(file);

        return -1;
    }
    //close file
    fclose(file);


    //return width
    return height;
}


// determine height of bmp image
uint32_t getBmpDataSize(char* filename)
{

    //check if file can be found
    if(existBmp(filename) == -1) return -1;

//alternative use function get height and get width and then multiplicate them and then again take it *3 (3 RGB coulours)
    //creating Var
    int32_t size, datasize_whole_image, datasize_headerinformation;
    FILE* file;

    //open file
    file = fopen(filename, "r");

    //set position of file to find out size of data
    fseek(file, 2, SEEK_SET);

    //read out data data_size
    if (fread(&datasize_whole_image,sizeof(int32_t),1,file) == 0)
    {
        //only jumpes in this if section if it could not be read
        printf("Failure! Data could not be read!\n");

        //close file
        fclose(file);

        //end function
        return -1;
    }

    //set position to offset of image_data because of header file
    fseek(file, 10, SEEK_SET);

    //read out data size header file
    if(fread(&datasize_headerinformation, sizeof(int32_t), 1, file) == 0)
    {
        //only jumpes in this if section if it could not be read
        printf("Failure! Data could not be read!\n");

        //close file
        fclose(file);

        //end funciton
        return -1;
    }

    //close file
    fclose(file);

    //calcuilate size
    size = datasize_whole_image - datasize_headerinformation;


    //end of function
    return size;
}



// conversion of rgb image to gray image
uint8_t* convertRgb2Gray(uint8_t* image, int32_t datasize)
{

    //creating an dynamic area with self reserved storage
    uint8_t* grey_image = (uint8_t *) malloc(sizeof(uint8_t) * datasize);

    //creating the grey-color out of the colord picture
    for(uint32_t i = 0; i < datasize ; i++)
    {
        *(grey_image + i) = 0.114 * *(image + 3*i) + 0.587 * *(image + 1 + 3*i) + 0.299 * *(image + 2 + 3*i);
    }

    //return pointer and end function
    return grey_image;
}



// get raw data of image
uint8_t getBmpData(char* filename, uint8_t* data)
{

    //check if file can be found
    if(existBmp(filename) == -1) return -1;

    //Creating Var for function
    FILE* file;
    uint32_t data_begin;


    //Opening File
    file = fopen(filename, "rb");

    //check if file was found
    if(file == NULL)
    {

        //if file wasn't found
        printf("File was not found");

        //close file
        fclose(file);

        //end funcition by returning -1
        return -1;
    }

    //check out, where data begins
    fseek(file, 10, SEEK_SET);

    //get the beginn of the image data
    if(fread(&data_begin, sizeof(uint32_t), 1, file) == 0)
    {
        //only jumpes in this if section if it could not be read
        printf("Failure! Data could not be read!\n");

        //close file
        fclose(file);

        //end funciton
        return -1;
    }

    //set position of file to image begin
    fseek(file, data_begin, SEEK_SET);

    //define data pointer as begin of image data
    if(fread(data, sizeof(uint8_t), getBmpDataSize(filename), file) == 0)
    {
        //only jumpes in this if section if it could not be read
        printf("Failure! Data could not be read!\n");

        //close file
        fclose(file);

        //end funciton
        return -1;
    }

    fclose(file);

    return 0;

}



void printfBMP(Image* img)
{
    //printng the first row
    printf("Width: %d  Height: %d \n",img -> width,img -> height);

    //creating loop for all rows
    for (int32_t i = img -> height -1; i >= 0; i--)
    {

        //creating loop for all cloulumbs
        for (int32_t j = 0; j < img -> width; j++)
        {

            //printing out the loop
            printf("%d",*(img -> data + j + img -> width * i));
            //printing out the spaces
            if(*(img -> data + j + img -> width * i) < 10)
            {
                printf("      ");
            }
            else if (*(img -> data + j + img -> width * i) < 100)
            {
                printf("     ");
            }
            else
            {
                printf("    ");
            }
        }
        //print new line
        printf("\n");
    }
}

void conv2D(Image* src, Image* dst, Kernel* krnl)
{



    //set the bottom line to 0
    for (uint32_t i = 0; i < src->width; i++){

        //set 0 to output
        *(dst->data + i) = 0;

    }

    //set the top line to 0
    for (uint32_t i = 0; i < src->width; i++){

        //set 0 to the ourput
        *(dst->data + (dst->datasize - dst->width) + i) = 0;
    }



    //loop through every line beginning at the socond highest
    for(uint32_t i = (src->height) - 2; i>=1; i--){

        //in every row start with writing a 0 to the left edge
        *(dst->data + (i * (src->width))) = 0;


        //loop from the 2 item through the row till the second last item
        for(uint32_t j = 1; j < src->width - 1; j++){

        //var for the kernal
        float value = 0;

                //calculate the pos in the file
                uint32_t pos = j + src->width * i;

                //cvalculate the value pos with kernel

                //first row
                for (uint8_t q = 0; q<3; q++){
                //value of the first row
                value += *(krnl->values + q) * *(src->data + pos + src->width -1 + q);
                }

                //second row
                for (uint8_t q = 0; q<3; q++){
                //value of the first row
                value += *(krnl->values + q + 3) * *(src->data + pos -1 + q);
                }

                //third row
                for (uint8_t q = 0; q<3; q++){
                //value of the first row
                value += *(krnl->values + q + 6) * *(src->data + pos - src->width -1 + q);
                }

                //loop though data an enter the item
                *(dst->data + (pos)) = value;
        }


    }


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


