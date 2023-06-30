#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: <%s> <notenliste>\n", argv[0]);
    }

    FILE* file;
    file = fopen(argv[1], "r");

    if(file == NULL)
    {
    printf("Datei konnte nicht geöffnet werden!\n");
    return -1;
    }

    char buffer [128];

    while((fgets(buffer, 128, file) != NULL))
    {
        printf("%s",buffer);
    }

    fseek(file,0,0);

    float average = 0;
    float tmp;
    int grades = 0;

    while((fgets(buffer, 128, file) != NULL))
    {
        if (sscanf(buffer,"%*[^;];%*[^;];%f", &tmp) != 1)
        {
            printf("Scannen fehlgeschlagen!\n");
        };

        average += tmp;
        grades++;
    }

    average = average/(grades-1);

    printf("Die durschnittsnote beträgt: %1.2f\n", average);

    fclose(file);
    return 0;
}
