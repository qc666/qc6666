#include<stdio.h>
#include<stdlib.h>

//int number = 0;				//统计连通图个数

typedef struct ArcNode {
	int adjvex;							//所指的点的位置；
	struct ArcNode* nextarc;			//指向下一个邻接点；
	int info;							//假设存了权重；
}*Arcnode;

typedef struct VNode {
	int data;							//每个顶点信息，这里详细指顶点有无后继指针，无为0
	Arcnode firstarc;					//顶点
}Vnode, * AdjList;

typedef struct {
	AdjList vertices;						//顶点数组
	int vexnum;								//图顶点数
	int arcnum;										//图边数
	int kind;								//图类型
}AlGraph;

typedef struct {
	int Adjvex;								//弧尾
	int Info;								//权值
}closedge;									//生成临时数组序号相当于弧头

typedef struct linklist {
	int head;								//弧尾
	int rear;								//弧头
	int weight;								//权值
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
	int* local1=(int*)malloc(sizeof(int)*G.vexnum);					//存储已经找到最小权值的顶点的集合大小为图中顶点个数
	Arcnode q = G.vertices[0].firstarc->nextarc;
	closedge* arcs = (closedge*)malloc(sizeof(closedge) * G.vexnum);//临时数组，用以存储每次变换顶点寻找最小权值
	link phead = (link)malloc(sizeof(Link));						//链表，用于存储每次找到最小权值边的信息
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
	//以下标为1点开始寻找，在临时数组中存储其邻接点的信息（权值与邻接点序号）
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
		}										//寻找每次临时数组中的最小权值，找到最小权值的临时数组的序号
		pbody = (link)malloc(sizeof(Link));		
		pbody->rear = local;
		pbody->head = arcs[local].Adjvex;
		pbody->weight = arcs[local].Info;
		pend->pnext = pbody;
		pend = pbody;
		local1[i] = local;						//舍弃该顶点的同时，将其存入找到最小权值的顶点集合
		arcs[local].Info = 0;
		arcs[local].Adjvex = -1;				//存储找到的序号中的内容，弧头弧尾权值；并将该顶点舍弃
		q = G.vertices[local].firstarc->nextarc;//在该顶点的基础上继续寻找与该顶点相连的邻接点的相关数据
		while (q != NULL)
		{				
			if (arcs[q->adjvex].Info == 0 && panduan(local1,G.vexnum, q->adjvex))
			{
				arcs[q->adjvex].Info = q->info;
				arcs[q->adjvex].Adjvex = local;
			}									//当该点的权值为0，且顶点（弧头）不是集合local1中的时，存入临时数组
			else if (arcs[q->adjvex].Info >= q->info && panduan(local1, G.vexnum, q->adjvex))
			{
				arcs[q->adjvex].Info = q->info;
				arcs[q->adjvex].Adjvex = local;
			}									//当该点的权值不为0，且顶点（弧头）不是集合local1中的时，
												//且权值小于临时数组中该顶点（弧头）的边的权值时，存入临时数组
			q = q->nextarc;
		}										// 该次循环用来将local号顶点的邻接点存入临时数组中
	}						//该循环用来寻找最小生成树
	pend->pnext = NULL;
	outputlink(phead);		//输出存储数据链表中的内容
}

//panduan函数用来判断弧头（即临时数组的序号）是否已经是找过的顶点（弧头）,不是返回true，是返回false
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
	fscanf(fp, "%d", &G->kind);													//默认为无向图
	fscanf(fp, "%d", &G->vexnum);
	fscanf(fp, "%d", &G->arcnum);												//默认该图符合图的要求
	G->vertices = (AdjList)malloc(sizeof(struct VNode) * G->vexnum);
	int i = 0;                                                               //记录输入的顶点个数
	while (i < G->vexnum)
	{
		G->vertices[i].firstarc = (Arcnode)malloc(sizeof(struct ArcNode));
		Arcnode q = G->vertices[i].firstarc;
		fscanf(fp, "%d", &q->adjvex);
		int k = 0;
//		fscanf(fp, "%d", &j);
		while (1)
		{
			if(fgetc(fp)=='\n'||feof(fp))
				break;
			Arcnode p = (Arcnode)malloc(sizeof(struct ArcNode));
			fscanf(fp, "%d", &p->adjvex);
			fscanf(fp, "%d", &p->info);
			q->nextarc = p;
			q = p;
			k++;
		}
		q->nextarc = NULL;
		G->vertices[i].data = k;
		i++;
	}
	fclose(fp);
}


/*
						在创建无向图的过程中，只对读取文件的内容作一定说明

					1. 第一行 依次为 图的类型、顶点数，边数
					2. 除第一行以外
						a. 第一个数字表示第几个顶点（默认顶点下标从0开始）
						b. 第二个数字表示该顶点有几个邻接点
						c. 此后 奇数号数字表示邻接点的下标
								偶数号数字表示邻接点与顶点的权值
					例如：
					  0(顶点数) 3(邻接点个数) 1(邻接点) 6(权值) 2 1 3 5
  */