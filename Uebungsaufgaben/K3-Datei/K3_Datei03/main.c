#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: <%s> <random_ints>\n", argv[0]);
    }


    FILE* file;
    file = fopen(argv[1], "r");

    if (file == NULL){
        printf("Datei konnte nicht geöffnet werden!\n");
        return -1;
    }


    char buffer[128];
    int sum = 0;
    int buf_int = 0;
    int n = 0;

    while((fgets(buffer,128,file)!=NULL))
    {
        sscanf(buffer,"%d", &buf_int);
        sum += buf_int;
        n += 1;
    }

    printf("Der Mittelwert der Zufallszahlen ist: %f\n", sum/(float)n);
    fclose(file);

    return 0;
}
