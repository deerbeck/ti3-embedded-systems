#include <stdio.h>
#include <stdlib.h>

char* encoding();

int main()
{
    char text[] = "Test";
    int s_len = strlen(text);
    char result[s_len +1];

    char key[] = "Hall";
    printf("s\n",encoding(text, key, result));
    printf("s\n",encoding(text, key, result));

    //printf("%c\n", encoding(en_text, key));
    return 0;
}


char* encoding(char* text, char* key, char* result)
{
    int s_len = strlen(text);

    for(int i = 0; i < s_len; i++)
    {
        *(result + i) = (*(text+i))^((0b00001111)&*(key+(i%s_len)));
        //*(result + i) = (*(text+i));
    }
    *(result+ (s_len +1)) = '\0';
}
