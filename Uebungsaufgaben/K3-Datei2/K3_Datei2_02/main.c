#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        if (argc != 2){
            printf("Usage: %s <head.txt> [<lines to print>]\n", argv[0]);
            return 1;
            }
    }
    FILE* head = fopen(argv[1], "r");
    if(head == NULL)
    {
        printf("Datei konnte nicht geöffnet werden.\n");
        return 2;
    }



    int lines_to_print = 10;
    if(argc == 3)
    {
        sscanf(argv[2], "%d", &lines_to_print);
    }
    char buffer[200];
    for(int i = 0; i<lines_to_print; i++)
    {
        fgets(buffer,200,head);
        printf(buffer);
    }

    fclose(head);
    return 0;

}
