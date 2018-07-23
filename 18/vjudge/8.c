#include<stdio.h>

int main()
{
    int a, b, t, N, f = 0;
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
        if(f != 0)
        {
            printf("\n");
        }
        else
        {
            f = 1;
        }
        printf("%d\n", a);
    }
}