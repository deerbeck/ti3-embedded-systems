#include <stdio.h>


int main(int argc, char* argv[])
{
	if ( argc != 3 )
	{
		fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
		return 1;
	}
	
	FILE* in = fopen(argv[1], "rb");
	if ( in == NULL )
	{
		fprintf(stderr, "file %s couldn't be opened\n", argv[1]);
		return 2;
	}
	
	FILE* out = fopen(argv[2], "wb");
	if ( out == NULL )
	{
		fclose(in);
		fprintf(stderr, "file %s couldn't be opened\n", argv[2]);
		return 3;
	}	
	
	char buffer[128];
	size_t r;
	while ( (r = fread(buffer, 1, 128, in)) != 0 )
	{
		fwrite(buffer, 1, r, out);
	}
	
	fclose(in);
	fclose(out);

	return 0;
}
