#include <stdio.h>
#include <stdlib.h>

int main()
{
    //create buffer variable to store console input
    char buffer = 0;

    //store console input into buffer variable
    scanf("%c", &buffer);

    //return input back to console
    printf("%c!\n", buffer);
    return 0;
}
