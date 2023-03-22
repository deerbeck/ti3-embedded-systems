#include <stdio.h>
int main(void)
{
    char a[16],b[16],c[16];
    printf("1. Buchstabe: ");

    //use fgets() function to get an correct input

    fgets(a, 16, stdin);
    printf("2. Buchstabe: ");

    fgets(b, 16, stdin);
    printf("3. Buchstabe: ");

    fgets(c, 16, stdin);

    //remove newline characters from the variables
    a[strcspn(a, "\n")] = 0;
    b[strcspn(b, "\n")] = 0;
    c[strcspn(c, "\n")] = 0;

    //print out given chars
    printf("Sie gaben ein : %s %s %s \n", a, b, c);

    return 0;
}
