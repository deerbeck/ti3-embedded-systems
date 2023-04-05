#include <stdio.h>
#include <stdlib.h>

char* encoding();

int main()
{
    char text[] = "Test";
    char key[] = "Hallo";
    encoding(text, key);
    return 0;
}


char* encoding(char* text, char* key)
{
    int s_len = strlen(text), test1 = 0, i = 0;
    char result[s_len + 1];

    while(*(text+i) != '\0')
    {
        i++;
        *(result + i) = (*(text+i))^((0b00001111)&*(key+(i%s_len)));

        //("%b\n", *(text));
        //printf("\n");
        printf("%d\n",i);
        //printf("%c\n", *(key+i));
    }
}
