#include <stdio.h>
#include "ti_bmp.h"


// main application
int main()
{
//    int32_t width = 200;
//    int32_t height = 100;
//    uint32_t datasize = height * width;
//    uint8_t image[datasize];
//    for (uint32_t i = 0; i < datasize; i++)
//    {
//        image[i] = 234;
//   }
//
//    saveBmpGray("hello.bmp", width, height, image);

    int32_t height = 300;
    int32_t width = 200;
    uint8_t circleCount = 2;
    int32_t* pwidth;
    uint8_t* pcircleCount;
    pwidth = &width;
    pcircleCount = &circleCount;

    char buffer[200];

    printf("Geben Sie die Bildbreite und die Anzahl der Kreise ein (getrennt durch Leerzeichen): \n");
    //Read Input from keyboard and print spacers to make consoleoutput more readable
    fgets(buffer, sizeof(buffer), stdin);
    printf("\n");

    // use sscanf() to extract integers from input line and check for correct input
    if (sscanf(buffer, "%d %hhu", pwidth, pcircleCount) == 2) {
        //print out input to give user feedback
        printf("Bild wird mit folgenden Parametern erzeugt:\n   -Bildbreite: %d\n   -Anzahl der Kreise: %d\n.\n.\n.\n", width, circleCount);
    } else {
        printf("Fehlerhafte Eingabe!\n");
    }

    //set height to width to get quadratic image
    height = width;

    //execute functions to generate blanc image and draw circles with given parameters
    char* image = genBackgroundImage(width, height, 222);
    drawCircles(image, width, height, circleCount, 10000, 7);
    saveBmpGray("firstimage.bmp", width, height, image);
    // end application successfully
    printf("\n------Bild erfolgreich erzeugt------\n");
    return 0;
}
