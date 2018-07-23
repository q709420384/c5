#ifndef QUEUE_H
#define QUEUE_H
#define ElemType int
typedef struct queue
{
	ElemType *base;
	int capacity;
	int front;
	int rear;
}queue;

void init_queue(queue* q);

void push(queue* q,ElemType x);

void pop(queue* q);

int empty(queue* q);

ElemType front(queue* q);

#endif
