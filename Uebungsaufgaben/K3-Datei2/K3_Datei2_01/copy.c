#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <copy_source> <copy_destination> \n", argv[0]);
        return -1;
    }

    FILE* src  = fopen(argv[1], "r");

    if (src == NULL)
    {
        printf("Datei konnte nicht geöffnet werden!\n");
        return -2;
    }

    FILE* dst = fopen(argv[2], "w");
    char c;
    while((c = fgetc(src)) != EOF)
    {
        fputc(c,dst);
    }


    fclose(src);
    fclose(dst);

    return 0;
}
