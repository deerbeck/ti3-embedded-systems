#include <stdio.h>


int add_rec(int a, int b, int c)
{
    if (a == 0 && b == 0 && c == 0)
        return 0;
    
    int a1 = a%10;
    int b1 = b%10;
    int sum = a1+b1+c;
    
    return sum%10 + 10*add_rec(a/10, b/10, sum/10);
}

int add(int a, int b)
{
    return add_rec(a, b, 0);
}



int main()
{
    int result = add(5738, 3884);
    printf("%d + %d = %d\n", 5738, 3384, result);
    
    return 0;
}
