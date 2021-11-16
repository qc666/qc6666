#include<stdio.h>
#include<stdlib.h>

int number = 0;				//统计连通图个数

typedef enum {
	DG = 1,					//有向图
	DN,						//有向网
	UDG,					//无向图
	UDN						//无向网
}Graphkind;

typedef struct ArcNode {
	int adjvex;							//所指的点的位置；
	struct ArcNode* nextarc;			//指向下一个邻接点；
	//char info;							//假设存了A,B,C......；
}*Arcnode;

typedef struct VNode {
	int data;							//每个顶点信息，这里详细指顶点有无后继指针，无为0
	Arcnode firstarc;
}Vnode, * AdjList;

typedef struct {
	AdjList vertices;						//顶点数组
	int vexnum;								//图顶点数
	int arcnum;										//图边数
	int kind;								//图类型
}AlGraph;


void creat_graph(AlGraph*);
void DFSTraverse1(AlGraph);
void DFSTraverse(AlGraph);
void DFS(AlGraph, int, bool*);

int main(void)
{
	AlGraph G;
	creat_graph(&G);
	DFSTraverse1(G);											//此处为邻接表式输出所有内容
	DFSTraverse(G);											   //此处为深度优先遍历
	if (number == 1)
		printf("一个连通图!\n");
	else
		printf("%d个连通图!\n", number);
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
	printf("%d号顶点位置为：%d\n", v , q->adjvex );
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
		printf("%d号顶点位置为：%d\n", i , q->adjvex );
		q = q->nextarc;
		if (q == NULL)
			printf("%d号顶点无邻接点！\n", i );
		printf("%d号顶点的邻接点内容为：\n", i );
		while (q != NULL)
		{
			printf("邻接点位置: %d\n", q->adjvex );
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
			printf("边数不符合图定义，程序退出！\n");
			exit(-1);
		}
		break;
	case 3:
		if (G->arcnum<0 || G->arcnum>(G->vexnum * (G->vexnum - 1)) / 2)
		{
			printf("边数不符合图定义，程序退出！\n");
			exit(-1);
		}
		break;
	case 2:
		if (G->arcnum<0 || G->arcnum>G->vexnum * (G->vexnum - 1))
		{
			printf("边数不符合图定义，程序退出！\n");
			exit(-1);
		}
		break;
	case 4:
		if (G->arcnum<0 || G->arcnum>(G->vexnum * (G->vexnum - 1)) / 2)
		{
			printf("边数不符合图定义，程序退出！\n");
			exit(-1);
		}
		break;
	}
	G->vertices = (AdjList)malloc(sizeof(struct VNode) * G->vexnum);
	int i = 0;                                                               //记录输入的顶点个数
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