#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void traversequeue(Queue*, int);
int computes_queue(Queue*);
int computes(Queue* , int );
void DeQueue(Queue* );

int main(void)
{
	Queue Q[4];
	int e = 0,people=1;
	while (e < 4)
	{
		initqueue(&Q[e]);
		e++;
	}
	while (1)
	{
		if (people == 50)
		{
			system("cls");
			e = 0;
			while (e < 4)
			{
				traversequeue(Q + e, e + 1);
				e++;
			}
			e = 0;
			while (e < 4)
			{
				while (Q[e].front != Q[e].rear)
					DeQueue(Q + e);
				e++;
			}
			break;
		}
		e = 0;
		while (e < 4)
		{
			printf("第 %d 行队列有 %d 个顾客\n", e + 1, computes_queue(&Q[e]));
			e++;
		}
		printf("\n\n来顾客了！\n\n");
		//来人
		int i = computes(Q,e);
		Enqueue(Q + i, people);
		people++;
		printf("\n\n当前剩下的顾客：\n");
		e = 0;
		while (e < 4)
		{
			traversequeue(Q + e, e + 1);
			e++;
		}
		//走人(随机队列，随机走人，每4回合走2个人)
		if (people % 4 == 0)
		{
			printf("\n\n顾客已走！\n");
			srand(time(NULL));
			e = 0;
			while (e < 2)
			{
				i = rand() % 4;
				if (computes_queue(Q + i) != 0)
				{
					DeQueue(Q + i);
					e++;
				}
			}
			e = 0;
			printf("\n\n当前剩下的顾客：\n");
			while (e < 4)
			{
				traversequeue(Q + e, e + 1);
				e++;
			}
		}
		system("pause");
		system("cls");
	}
	system("pause");
	return 0;
}

void DeQueue(Queue* Q)
{
	Data* q = Q->front->next;
	printf("%d 号顾客已走！\n", q->data);
	Q->front->next = q->next;
	if (q == Q->rear)
		Q->rear = Q->front;
	free(q);
}

int computes(Queue* Q,int e)
{
	int i, j = 0, k = 0;
	i = computes_queue(Q + j);
	while (j < e)
	{
		if (i > computes_queue(Q + j))
		{
			i = computes_queue(Q + j);
			k = j;
		}
		j++;
	}
	return k;
}

int computes_queue(Queue* Q)
{
	if (Q->front == Q->rear)
		return 0;
	int i = 0;
	Data* q = Q->front->next;
	while (q)
	{
		q = q->next;
		i++;
	}
	return i;
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

void traversequeue(Queue* Q, int e)
{
	if (Q->front == Q->rear)
	{
		printf("第 %d 号队列为空，无人排队！\n", e, e);
		return;
	}
	printf("第 %d 号队列排队人员为：\n", e);
	Data* q = Q->front->next;
	while (q)
	{
		printf("%d ", q->data);
		q = q->next;
	}
	putchar(10);
	putchar(10);
}