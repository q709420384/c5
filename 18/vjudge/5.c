#include<stdio.h>

int main()
{
    int a, b, t, N;
    scanf("%d", &N);
    while( N-- )
    {
        a = 0;
        scanf("%d", &t);
        while(t--)
        {
            scanf("%d", &b);
            a += b;
        }
        printf("%d\n", a);
    }
}