#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* config;
    char* line[255];

    config = fopen("../config.txt", "r");

    if (config == NULL)
    {
        printf("Could not open/find file!\n");
        return -1;
    }

    while((fgets(line, 255, config)) != NULL)
    {
        printf("%s", line);
    }

    fclose(config);
    return 0;
}
