#include<stdio.h>
#include"queue.h"

int main()
{
    queue qu;
    init_queue(&qu);
    push(&qu, 1);
    push(&qu, 3);
    push(&qu, 4);
    while(!empty(&qu))
    {
        printf("%d\n", front(&qu));
        pop(&qu);
    }
}