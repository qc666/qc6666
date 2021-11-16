#include<stdio.h>
#include<stdlib.h>

int number = 0;				//ͳ����ͨͼ����

typedef enum {
	DG = 1,					//����ͼ
	DN,						//������
	UDG,					//����ͼ
	UDN						//������
}Graphkind;

typedef struct ArcNode {
	int adjvex;							//��ָ�ĵ��λ�ã�
	struct ArcNode* nextarc;			//ָ����һ���ڽӵ㣻
	//char info;							//�������A,B,C......��
}*Arcnode;

typedef struct VNode {
	int data;							//ÿ��������Ϣ��������ϸָ�������޺��ָ�룬��Ϊ0
	Arcnode firstarc;
}Vnode, * AdjList;

typedef struct {
	AdjList vertices;						//��������
	int vexnum;								//ͼ������
	int arcnum;										//ͼ����
	int kind;								//ͼ����
}AlGraph;


void creat_graph(AlGraph*);
void DFSTraverse1(AlGraph);
void DFSTraverse(AlGraph);
void DFS(AlGraph, int, bool*);

int main(void)
{
	AlGraph G;
	creat_graph(&G);
	DFSTraverse1(G);											//�˴�Ϊ�ڽӱ�ʽ�����������
	DFSTraverse(G);											   //�˴�Ϊ������ȱ���
	if (number == 1)
		printf("һ����ͨͼ!\n");
	else
		printf("%d����ͨͼ!\n", number);
	system("pause");
	return 0;
}

void DFSTraverse(AlGraph G)
{
	int v = 0;
	bool* visited = (bool*)malloc(sizeof(bool) * G.vexnum);
	for (; v < G.vexnum; v++)
		visited[v] = false;
	for (v = 0; v < G.vexnum; v++)
		if (!visited[v])
		{
			DFS(G, v, visited);
			number++;
		}
}

void DFS(AlGraph G, int v, bool* visited)
{
	int w;
	visited[v] = true;
	Arcnode q = G.vertices[v].firstarc;
	printf("%d�Ŷ���λ��Ϊ��%d\n", v , q->adjvex );
	q = q->nextarc;
	while (q != NULL)
	{
		w = q->adjvex;
		if (!visited[w])
			DFS(G, w, visited);
		q = q->nextarc;
	}
}

void DFSTraverse1(AlGraph G)
{
	int i = 0;
	while (i < G.vexnum)
	{
		Arcnode q = G.vertices[i].firstarc;
		printf("%d�Ŷ���λ��Ϊ��%d\n", i , q->adjvex );
		q = q->nextarc;
		if (q == NULL)
			printf("%d�Ŷ������ڽӵ㣡\n", i );
		printf("%d�Ŷ�����ڽӵ�����Ϊ��\n", i );
		while (q != NULL)
		{
			printf("�ڽӵ�λ��: %d\n", q->adjvex );
			q = q->nextarc;
		}
		i++;
	}
}

void creat_graph(AlGraph* G)
{
	FILE* fp = fopen("matrix.txt", "r+");
	fscanf(fp,"%d", &G->kind);
	fscanf(fp, "%d", &G->vexnum);
	fscanf(fp, "%d", &G->arcnum);
	switch (G->kind)
	{
	case 1:
		if (G->arcnum<0 || G->arcnum>G->vexnum * (G->vexnum - 1))
		{
			printf("����������ͼ���壬�����˳���\n");
			exit(-1);
		}
		break;
	case 3:
		if (G->arcnum<0 || G->arcnum>(G->vexnum * (G->vexnum - 1)) / 2)
		{
			printf("����������ͼ���壬�����˳���\n");
			exit(-1);
		}
		break;
	case 2:
		if (G->arcnum<0 || G->arcnum>G->vexnum * (G->vexnum - 1))
		{
			printf("����������ͼ���壬�����˳���\n");
			exit(-1);
		}
		break;
	case 4:
		if (G->arcnum<0 || G->arcnum>(G->vexnum * (G->vexnum - 1)) / 2)
		{
			printf("����������ͼ���壬�����˳���\n");
			exit(-1);
		}
		break;
	}
	G->vertices = (AdjList)malloc(sizeof(struct VNode) * G->vexnum);
	int i = 0;                                                               //��¼����Ķ������
	while (i < G->vexnum)
	{
		G->vertices[i].firstarc = (Arcnode)malloc(sizeof(struct ArcNode));
		Arcnode q = G->vertices[i].firstarc;
		fscanf(fp, "%d", &q->adjvex);
		int j, k = 0;
		fscanf(fp,"%d", &j);
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
			fscanf(fp,"%d", &p->adjvex);
			//p->adjvex--;
			q->nextarc = p;
			q = p;
			k++;
		}
		q->nextarc = NULL;
		G->vertices[i].data = j;
		i++;
	}
}