#include <stdio.h>
#include <stdint.h>

int main()
{
    int width = 64;
    int height = 128;
    uint8_t image[width*height];
    for(int i = 0; i < width*height; i++)
    {
        image[i] = i%255;
    }
    
    printf("(0, 0) = %d; (0, width-1) = %d\n", image[0], image[width-1]);
    printf("(height-1, 0) = %d; (height-1, width-1) = %d\n", image[width*(height-1)], image[width*height-1]);
    
    printf("\n");
    
    // Spiegeln
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width/2; col++)
        {
            uint8_t tmp = image[row*width+width-1-col];
            image[row*width+width-1-col] = image[row*width + col];
            image[row*width + col] = tmp;
        }
    }
    
    printf("(0, 0) = %d; (0, width-1) = %d\n", image[0], image[width-1]);
    printf("(height-1, 0) = %d; (height-1, width-1) = %d\n", image[width*(height-1)], image[width*height-1]);
    
    return 0;
}
