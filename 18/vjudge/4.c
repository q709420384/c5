#include<stdio.h>

int main()
{
    int a, b, N;
    
    while(scanf("%d", &N))
    {
        if(N == 0)
            break;
        a = 0;
        while(N--)
        {
            scanf("%d", &b);
            a += b;
        }
        
        printf("%d\n", a);
    }
}