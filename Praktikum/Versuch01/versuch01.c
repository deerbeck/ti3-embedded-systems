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
    //initialize parameters
    int32_t height = 300;
    int32_t width = 200;
    uint8_t circleCount = 2;
    char name[200];
    char filename[200];
    //buffer for input
    char buffer[200];

    while(1){
    printf("Geben Sie den Basisdateinamen , die Bildbreite und die Anzahl der Kreise ein (getrennt durch Leerzeichen): \n");
    //Read Input from keyboard and print spacers to make consoleoutput more readable
    fgets(buffer, sizeof(buffer), stdin);
    printf("\n");

    // use sscanf() to extract integers from input line and check for correct input (just use adress from width and circleCount for more readability)
    if (sscanf(buffer, "%s %d %hhu",name, &width, &circleCount) == 3) {
        //check for negative input and end program
        if(width < 0 || circleCount < 0){
        printf("Fehlerhafte Eingabe, Programm wird beendet!\n\n");
        break;
        }

        //print out input to give user feedback
        printf("Bild wird mit folgenden Parametern erzeugt:\n   -Basisdateiname: %s\n   -Bildbreite: %d\n   -Anzahl der Kreise: %d\n.\n.\n.\n", name, width, circleCount);
    } else {
        printf("Fehlerhafte Eingabe, Programm wird beendet!\n\n");
        break;
    }

    //set height to width to get quadratic image
    height = width;
    //Concatenate string with sprintf function to generate the filename
    sprintf(filename, "%s_%d_%d.bmp", name, width, circleCount);

    //execute functions to generate blanc image and draw circles with given parameters
    char* image = genBackgroundImage(width, height, 222);
    drawCircles(image, width, height, circleCount, 10000, 7);
    saveBmpGray(filename, width, height, image);

    //free allocated storage to prevent overflow
    free(image);
    // end application successfully
    printf("\n------Bild erfolgreich erzeugt------\n\n");
    }
    return 0;
}
