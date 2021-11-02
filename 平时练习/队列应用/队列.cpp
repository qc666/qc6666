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
void traversequeue(Queue*,int );
int computes_firstelement(int );

int main(void)
{
	Queue Q[10];
	int e = 0;
	while (e < 10)
	{
		initqueue(&Q[e]);
		e++;
	}
	printf("请输入队列元素，元素为0表示结束！\n");
	while (1)
	{
		int i;
		scanf("%d", &e);
		if (e == 0)
			break;
		i=computes_firstelement(e);
		switch (i)
		{
			case 0:
				Enqueue(&Q[0], e);
				break;
			case 1:
				Enqueue(&Q[1], e);
				break;
			case 2:
				Enqueue(&Q[2], e);
				break;
			case 3:
				Enqueue(&Q[3], e);
				break;
			case 4:
				Enqueue(&Q[4], e);
				break;
			case 5:
				Enqueue(&Q[5], e);
				break;
			case 6:
				Enqueue(&Q[6], e);
				break;
			case 7:
				Enqueue(&Q[7], e);
				break;
			case 8:
				Enqueue(&Q[8], e);
				break;
			case 9:
				Enqueue(&Q[9], e);
				break;
		}
	}
	e = 0;
	putchar(10);
	putchar(10);
	while (e < 10)
	{
		traversequeue(&Q[e],e);
		e++;
	}
	return 0;
}


int computes_firstelement(int e)
{
		e = e % 10;
		return e;
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

void traversequeue(Queue* Q,int e)
{
	if (Q->front == Q->rear)
	{
		printf("第 %d 号队列为空，无个位为 %d 的元素！\n", e,e);
		return;
	}
	printf("第 %d 号队列元素为：\n", e);
	Data* q = Q->front->next;
	while (q)
	{
		printf("%d ", q->data);
		q = q->next;
	}
	putchar(10);
	putchar(10);
}