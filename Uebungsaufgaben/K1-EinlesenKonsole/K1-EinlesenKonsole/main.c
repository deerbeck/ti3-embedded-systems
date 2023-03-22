#include <stdio.h>
int main(void)
{
    char a[16],b[16],c[16];
    printf("1. Buchstabe: ");

    //use gets() function to get an correct input

    gets(a);
    printf("2. Buchstabe: ");

    gets(b);
    fflush(stdin);
    printf("3. Buchstabe: ");

    gets(c);
    fflush(stdin);
    printf("Sie gaben ein : %s %s %s \n", a, b, c);

    return 0;
}
