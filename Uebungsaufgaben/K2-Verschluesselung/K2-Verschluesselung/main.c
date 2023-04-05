#include <stdio.h>
#include <stdlib.h>

char* encoding();

int main()
{
    char text[] = "Hallo Welt";
    char key[] = "secret";


    printf("%s\n", text);
    encoding(text,key);

    printf("%s\n", text);
    encoding(text,key);
    printf("%s\n", text);

    //printf("%c\n", encoding(en_text, key));
    return 0;
}


char* encoding(char* text, char* key)
{
    int s_len = strlen(text), k_len = strlen(key);
    char buffer[s_len +1];

    for(int i = 0; i < s_len; i++)
    {
        *(buffer + i) = (*(text+i))^((0b00001111)&*(key+(i%k_len)));
        *(text +i) = *(buffer +i);
    }
}
