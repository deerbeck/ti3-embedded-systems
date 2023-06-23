#ifndef TI_BMP_H
#define TI_BMP_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>


/**
 * generates a square image with constant background color
 *
 * @param width arbitrary width of an image (e.g. 100, 101, ...)
 * @param height arbitrary height of an image (e.g. 100, 101, ...)
 * @param bgcolor gray value for image background (0..255), typically 240
 * @return dynamically generated image of size (height*width)
 */
uint8_t* genBackgroundImage(int32_t width, int32_t height, uint8_t bgcolor);


/**
 * draws concentric circles in a given image
 *
 * @param image 1-d image array of size width x height
 * @param width arbitrary width of an image (e.g. 100, 101, ...)
 * @param height arbitrary height of an image (e.g. 100, 101, ...)
 * @param circleCount number of concentric circles to be drawn in image
 * @param pointsPerCircle number of points to be calculated for each circle for smooth drawing
 * @param color gray value for circle line color (0..255), typically 5
 */
void drawCircles(uint8_t* image, int32_t width, int32_t height, uint8_t circleCount, uint32_t pointsPerCircle, uint8_t color);


/**
 * saves gray image to filesystem in bmp format
 *
 * @param filename name of file including suffix (.bmp) for saving
 * @param width width of image in pixel
 * @param height height of image in pixel
 * @param data 1-d image array of size width x height
 * @return success indicator of saving
 * @retval 0 file could be saved successfully
 * @retval -1 file couldn't be created
 */
uint8_t saveBmpGray(char* filename, int32_t width, int32_t height, uint8_t* data);

/**
 * checks if file with filename exists
 *
 * @param filename filename of file to be checked
 * @retval 0 file exists
 * @retval -1 file doesn't exit
 */
int32_t existBmp(char* filename);

/**
 * determines width of image out of BMP header
 *
 * @param filename filename of bmp image to checked
 * @retval >0 width of image in pixel
 * @retval -1 width couldn't be determined
 */
int32_t getBmpWidth(char* filename);

/**
 * determines height of image out of BMP header
 *
 * @param filename filename of bmp image to checked
 * @retval >0 height of image in pixel
 * @retval -1 height couldn't be determined
 */
int32_t getBmpHeight(char* filename);

/**
 * determines size of pixel data block out of BMP header
 *
 * @param filename filename of bmp image to checked
 * @retval >0 data size of bmp image
 * @retval -1 data size couldn't be determined
 */
uint32_t getBmpDataSize(char* filename);

/**
 * converts rgb image to gray image
 *
 * @param image pointer to rgb image data
 * @param datasize size of gray image data
 * @retval pointer to dynamically created gray image
 */
uint8_t* convertRgb2Gray(uint8_t* image, int datasize);

/**
 * gets pointer to pixel data of image out of BMP header
 *
 * @param filename filename of bmp image to checked
 * @param data pointer to image data
 * @retval 0 data could be read
 * @retval -1 data couldn't be read
 */
uint8_t getBmpData(char* filename, uint8_t* data);


// TODO: Struct

//adding the first structur as an typedef
typedef struct Kernel {

//attributes of the stucture
char name[32];
float values[9];

} Kernel;

//adding the structure Image as an typedef
typedef struct Image{

//adding attributes to the structure
int32_t width;
int32_t height;
uint32_t datasize;
uint8_t* data;

} Image;

/**
 * prints image to stdout
 *
 * @param img image structure holding image information
 */
void printfBMP(Image* img);

/**
 * applies convolution to image based on kernel and generates output image
 *
 * @param src image structure holding source image information
 * @param dst image structure holding destination image information
 * @param krnl kernel structure holding kernel values
 */
void conv2D(Image* src, Image* dst, Kernel* krnl);

#endif
