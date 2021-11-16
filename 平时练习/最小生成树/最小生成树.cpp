#include<stdio.h>
#include<stdlib.h>

//int number = 0;				//ͳ����ͨͼ����

typedef struct ArcNode {
	int adjvex;							//��ָ�ĵ��λ�ã�
	struct ArcNode* nextarc;			//ָ����һ���ڽӵ㣻
	int info;							//�������Ȩ�أ�
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

typedef struct {
	int Adjvex;
	int Info;
}closedge;

typedef struct linklist {
	int head;
	int rear;
	int weight;
	struct linklist* pnext;
}Link, * link;


void creat_graph(AlGraph*);
void MiniSpantree(AlGraph);
void outputlink(link );
bool panduan(int*,int,int);

int main(void)
{
	AlGraph G;
	creat_graph(&G);
	MiniSpantree(G);
	system("pause");
	return 0;
}

void MiniSpantree(AlGraph G) 
{
	int i = 0;
	int local = i;
	int* local1=(int*)malloc(sizeof(int)*G.vexnum);
	Arcnode q = G.vertices[0].firstarc->nextarc;
	closedge* arcs = (closedge*)malloc(sizeof(closedge) * G.vexnum);
	link phead = (link)malloc(sizeof(Link));
	link pbody,pend=phead;
	for (; i < G.vexnum; i++)
	{
		arcs[i].Info = 0;
		arcs[i].Adjvex = -1;
		local1[i] = -1;
	}
	local1[0] = 0;
	while (q != NULL)
	{
		arcs[q->adjvex].Info = q->info;
		arcs[q->adjvex].Adjvex = 0;
		q = q->nextarc;
	}
	for (i = 1; i < G.vexnum; i++)
	{
		int k = 10000;
		for (int j = 0; j < G.vexnum; j++)
		{
			if (arcs[j].Adjvex != -1 &&  arcs[j].Info < k)
			{
				k = arcs[j].Info;
				local = j;
			}
		}
		pbody = (link)malloc(sizeof(Link));
		pbody->rear = local;
		pbody->head = arcs[local].Adjvex;
		pbody->weight = arcs[local].Info;
		pend->pnext = pbody;
		pend = pbody;
		local1[i] = local;
		arcs[local].Info = 0;
		arcs[local].Adjvex = -1;
		q = G.vertices[local].firstarc->nextarc;
		while (q != NULL)
		{
			if (arcs[q->adjvex].Info == 0 && panduan(local1,G.vexnum, q->adjvex))
			{
				arcs[q->adjvex].Info = q->info;
				arcs[q->adjvex].Adjvex = local;
			}
			else if (arcs[q->adjvex].Info >= q->info && panduan(local1, G.vexnum, q->adjvex))
			{
				arcs[q->adjvex].Info = q->info;
				arcs[q->adjvex].Adjvex = local;
			}
			q = q->nextarc;
		}
	}
	pend->pnext = NULL;
	outputlink(phead);
}

bool panduan(int* local, int i,int k)
{
	int j = 0;
	while (j < i)
	{
		if (local[j] == k)
			return false;
		j++;
	}
	return true;
}

void outputlink(link phead)
{
	link p = phead->pnext;
	while (p!=NULL)
	{
		printf("%d %d %d\n", p->head, p->rear, p->weight);
		p = p->pnext;
	}
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
			q->info = -1;
			i++;
			continue;
		}
		while (k < j)
		{
			Arcnode p = (Arcnode)malloc(sizeof(struct ArcNode));
			fscanf(fp, "%d", &p->adjvex);
			fscanf(fp, "%d", &p->info);
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