#include <stdio.h>


void print_rec(int num)
{
    printf("%d ", num);
    if (num == 0)
        return;
    
    print_rec(num-1);
    printf("%d ", num);
}

int main()
{
    print_rec(5);
}
