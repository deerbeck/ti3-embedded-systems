#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a, b, c;
    char buffer[128];

    printf("1. Buchstabe: ");
    fgets(buffer, 100, stdin);
    a = buffer[0];

    printf("2. Buchstabe: ");
    fgets(buffer, 100, stdin);
    b = buffer[0];

    printf("3. Buchstabe: ");
    fgets(buffer, 100, stdin);
    c = buffer[0];

    printf("Sie gaben ein: %c %c %c\n", a, b, c);

    return 0;
}
