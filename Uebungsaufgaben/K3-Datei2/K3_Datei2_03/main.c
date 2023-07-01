#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 3 && argc != 2)
    {
        printf("Usage: %s <tail.txt> [lines to print]\n",argv[0]);
        return -1;
    }

    FILE* tail = fopen(argv[1], "r");

    if(tail == NULL)
    {
        printf("Datei konnte nicht geöffnet werden!\n");
        return -2;
    }

    int lines_to_print = 10;

    if (argc == 3)
    {
        sscanf(argv[2],"%d", &lines_to_print);
    }


    char buffer[200];
    int lines = 0;
    while(fgets(buffer, 200, tail) != NULL)
    {
        lines++;
    }

    fseek(tail, 0, 0);

    int line = 0;
    int start = (lines - lines_to_print);

    if (start < 0) start = 0;
    while(fgets(buffer, 200, tail)!= NULL)
    {
        if(line >= (start))
        {
            printf("%s",buffer);
        }
        line++;
    }

    return 0;
}
