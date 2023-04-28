#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if ( argc != 3 )
    {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "rb");
    if ( in == NULL )
    {
        printf("File %s couldn't be opened!\n", argv[1]);
        return 2;
    }

    FILE* out = fopen(argv[2], "wb");
    if ( out == NULL )
    {
        printf("File %s couldn't be opened!\n", argv[2]);
        fclose(in);
        return 3;
    }

    char buffer[128];
    size_t r;
    int i = 0;
    while ( (r = fread(buffer, sizeof(char), 128, in)) != 0 )
    {
        fwrite(buffer, sizeof(char), r, out);
        i += r;
        printf("%d bytes gelesen\n", i);
    }

    fclose(out);
    fclose(in);

    return 0;
}
