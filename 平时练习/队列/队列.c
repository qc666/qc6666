#include <stdio.h>
#include <stdlib.h>

typedef struct DATA {
	int data;
	struct DATA* next;
}Data;

typedef struct queue {
	Data* front;
	Data* rear;
}Queue;

void initqueue(Queue*);
void Enqueue(Queue*, int);
void traversequeue(Queue* );

int main(void)
{
	Queue Q;
	initqueue(&Q);
	Enqueue(&Q, 1);
	Enqueue(&Q, 2);
	traversequeue(&Q);
	return 0;
}

void initqueue(Queue* Q)
{
	Q->front = (Data*)malloc(sizeof(Data));
	if (!Q->front)
	{
		printf("动态内存申请失败，程序退出！\n");
		exit(-1);
	}
	Q->rear = Q->front;
	Q->front->next = NULL;
}

void Enqueue(Queue* Q, int e)
{
	Data* q = (Data*)malloc(sizeof(Data));
	if (!q)
	{
		printf("动态内存申请失败，程序退出！\n");
		exit(-1);
	}
	q->data = e;
	q->next = NULL;
	Q->rear->next = q;
	Q->rear = q;
}

void traversequeue(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("队列为空，无法遍历队列！\n");
		return;
	}
	Data* q = Q->front->next;
	while (q)
	{
		printf("%d ", q->data);
		q = q->next;
	}
}