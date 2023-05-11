#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //check if file is used correctly
    if ( argc != 2 )
    {
        fprintf(stderr, "Usage: %s <number of random integers>\n", argv[0]);

        return 1;
    }

    //convert string to integer and limit max number of random numbers to 100
    int number_of_ints = atoi(argv[1]);

    if (number_of_ints > 100)
    {
        number_of_ints = 100;
    }


    //Set seed for srand function
    time_t t;
    srand((unsigned) time(&t));
    int iRandom;

    //open file where random ints should be written:
    FILE* file = fopen("random_ints.txt", "w");

    for (int i = 0; i < number_of_ints-1; i++)
    {
        //get random int and buffer it in iRandom
        iRandom = rand() % 100;
        //use formated writing into file and put random number in each line
        fprintf(file, "%d\n",iRandom);
    }



    //Close file after usage
    fclose(file);
    return 0;
}
