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

/*
gets pointerindex from x and y coordinate
*/
uint64_t pointer_calc(uint32_t x, uint32_t y, uint32_t height);
