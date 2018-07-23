#include<stdio.h>

int jc(int n)
{
    int s = n;
    s && (s *= jc(n - 1));
    s && return s;
    return 1;
}

int main()
{
    printf("%d\n", jc(10));
}
