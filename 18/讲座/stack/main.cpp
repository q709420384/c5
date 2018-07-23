#include<stdio.h>
#include"stack.h"

int main()
{
    stack st;
    init_stack(&st);
    push(&st, 1);
    push(&st, 2);
    push(&st, 3);
    while(!empty(&st))
    {
        printf("%d\n", gettop(&st));
        pop(&st);
    }
}