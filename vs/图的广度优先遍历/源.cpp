#include<stdio.h>
#include<stdlib.h>

int number = 0;				//ͳ����ͨͼ����

typedef struct ArcNode {
	int adjvex;							//��ָ�ĵ��λ�ã�
	struct ArcNode* nextarc;			//ָ����һ���ڽӵ㣻
	//int info;							//�������Ȩ�أ�
}*Arcnode;

typedef struct VNode {
	int data;							//ÿ��������Ϣ��������ϸָ�������޺��ָ�룬��Ϊ0
	Arcnode firstarc;					//����
}Vnode, * AdjList;

typedef struct {
	AdjList vertices;						//��������
	int vexnum;								//ͼ������
	int arcnum;										//ͼ����
	int kind;								//ͼ����
}AlGraph;

typedef struct DATA {
	int data;
	struct DATA* next;
}Data;

typedef struct queue {
	Data* front;
	Data* rear;
}Queue;


void initqueue(Queue*);
void creat_graph(AlGraph*);
void BFSTraverse(AlGraph);
void Enqueue(Queue*,int);
int Dequeue(Queue*);
bool Empty_queue(Queue* );

int main(void)
{
	AlGraph G;
	creat_graph(&G);
	printf("������ȱ���:\n");
	BFSTraverse(G);											   //�˴�Ϊ������ȱ���
	if (number == 1)
		printf("\n��ͨͼ!\n");
	else
		printf("\n%d����ͨ����!\n", number);
	system("pause");
	return 0;
}

void BFSTraverse(AlGraph G)
{
	Queue Q;
	Arcnode q;
	initqueue(&Q);
	int v = 0;
	bool* visited = (bool*)malloc(sizeof(bool) * G.vexnum);
	for (; v < G.vexnum; v++)
		visited[v] = false;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v])
		{
			visited[v] = true;
			q = G.vertices[v].firstarc;
			printf("   %d", q->adjvex);
			Enqueue(&Q,q->adjvex);
			while (!Empty_queue(&Q))
			{
				v = Dequeue(&Q);
				q = G.vertices[v].firstarc;
				while (q != NULL)
				{
					if (!visited[q->adjvex])
					{
						visited[q->adjvex] = true;
						printf("   %d", q->adjvex);
						Enqueue(&Q, q->adjvex);
					}
					q = q->nextarc;
				}
			}
			number++;
//			Dequeue(&Q);
		}
}

bool Empty_queue(Queue* Q)
{
	if (Q->front == Q->rear)
		return true;
	else
		return false;
}

void Enqueue(Queue* Q,int i)
{
	Data* q = (Data*)malloc(sizeof(struct DATA));
	q->data = i;
	q->next = NULL;
	Q->rear->next = q;
	Q->rear = q;
}

int Dequeue(Queue* Q)
{
	Data* q = Q->front->next;
	int i = q->data;
	Q->front->next = q->next;
	if (q == Q->rear)
		Q->rear = Q->front;
	free(q);
	return i;
}

void initqueue(Queue* Q)
{
	Q->front = (Data*)malloc(sizeof(struct DATA));
	Q->rear = Q->front;
	Q->front->next = NULL;
}

void creat_graph(AlGraph* G)
{
	FILE* fp = fopen("matrix.txt", "r+");
	fscanf(fp, "%d", &G->kind);													//Ĭ��Ϊ����ͼ
	fscanf(fp, "%d", &G->vexnum);
	fscanf(fp, "%d", &G->arcnum);												//Ĭ�ϸ�ͼ����ͼ��Ҫ��
	G->vertices = (AdjList)malloc(sizeof(struct VNode) * G->vexnum);
	int i = 0;                                                               //��¼����Ķ������
	while (i < G->vexnum)
	{
		G->vertices[i].firstarc = (Arcnode)malloc(sizeof(struct ArcNode));
		Arcnode q = G->vertices[i].firstarc;
		fscanf(fp, "%d", &q->adjvex);
		int j, k = 0;
		fscanf(fp, "%d", &j);
		if (j == 0)
		{
			G->vertices[i].data = j;
			q->nextarc = NULL;
			i++;
			continue;
		}
		while (k < j)
		{
			Arcnode p = (Arcnode)malloc(sizeof(struct ArcNode));
			fscanf(fp, "%d", &p->adjvex);
			//p->adjvex--;
			q->nextarc = p;
			q = p;
			k++;
		}
		q->nextarc = NULL;
		G->vertices[i].data = j;
		i++;
	}
	fclose(fp);
}