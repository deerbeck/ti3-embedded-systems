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
    int s_len = strlen(text), test1 = 0;
    char result[s_len + 1];

    for(int i = 0; i < s_len; i++)
    {

        result[i] = (*(text+i))^((0b00001111)&*(key+i));

        //("%b\n", *(text));
        //printf("\n");
        printf("%c\n",result[i]);
        //printf("%c\n", *(key+i));
    }
}
