#include<stdio.h>
#include<stdlib.h>

int number = 0;				//统计连通图个数

typedef struct ArcNode {
	int adjvex;							//所指的点的位置；
	struct ArcNode* nextarc;			//指向下一个邻接点；
	int info;							//假设存了权重；
	int info_number;					//权重序号
	char tag;							//活动是否关键（关键为 *，不关键为空格符）
}*Arcnode;

typedef struct VNode {
	int Endegree;						//入度
	int data;							//每个顶点信息，这里详细指顶点有无后继指针，无为0
	Arcnode firstarc;					//顶点
}Vnode, * AdjList;

typedef struct {
	Vnode vertices[100];
//	AdjList vertices;						//顶点数组
	int vexnum;								//图顶点数
	int arcnum;										//图边数
	int kind;								//图类型
}AlGraph;

typedef struct DATA {
	int data;								//栈中入度为零顶点序号
	struct DATA* next;
}Data;

typedef struct STACK {
	Data* top;								//栈顶
	Data* bottom;							//栈底
}Stack,*stack;


void creat_graph(AlGraph*);
void Toposort(AlGraph* );
void countdegree(AlGraph* );
void initStack(stack);
void pushStack(stack ,int);
int popStack(stack );
void CriticalPath(AlGraph*);
bool TopoSort(AlGraph* , stack ,int*);
void keyroad(AlGraph* , int* , int* , int* , int* );

int main(void)
{
	AlGraph G;
	creat_graph(&G);
	Toposort(&G);
	printf("\n\n\n");
	CriticalPath(&G);
	system("pause");
	return 0;
}

void CriticalPath(AlGraph* G)
{
	Stack T;
	Arcnode q;
	int* ve = (int*)malloc(sizeof(int) * G->vexnum);
	int* vl = (int*)malloc(sizeof(int) * G->vexnum);
	int* ee = (int*)malloc(sizeof(int) * G->arcnum);
	int* el = (int*)malloc(sizeof(int) * G->arcnum);
	if (TopoSort(G, &T, ve) == false)
	{
		printf("该有向网有回路！程序退出!\n");
		exit(-1);
	}
	for (int i = 0; i < G->vexnum; i++)
		vl[i] = ve[G->vexnum-1];											//事件最迟发生时间初始化（假设为全程完成的时间）
	while (T.bottom != T.top)
	{
		int local = popStack(&T);
		q = G->vertices[local].firstarc->nextarc;
		while (q != NULL)
		{
			if (vl[q->adjvex] - q->info < vl[local])
				vl[local] = vl[q->adjvex] - q->info;
			q = q->nextarc;
		}
	}
	for (int j = 0; j < G->vexnum; j++)
	{
		q = G->vertices[j].firstarc->nextarc;
		while (q != NULL)
		{
			ee[q->info_number] = ve[j];
			el[q->info_number] = vl[q->adjvex] - q->info;
			if (ee[q->info_number] == el[q->info_number])
				q->tag = '*';
			else
				q->tag = ' ';
			q = q->nextarc;
		}
	}
	keyroad(G, ve, vl, ee, el);
}

void keyroad(AlGraph* G, int* ve, int* vl, int* ee, int* el)
{
	int i = 0, local;
	printf("事件\t最早发生时间\t最晚发生时间\t\n");
	for (i = 0; i < G->vexnum; i++)
		printf("%3d \t%5d \t\t%5d\n",i+1,ve[i],vl[i]);
	printf("\n\n活动\t最早发生时间\t最晚发生时间\t\n");
	for (i = 0; i < G->arcnum; i++)
		printf("%3d \t%5d \t\t%5d\n", i+1 , ee[i], el[i]);
	printf("\n\n关键路径为(以事件为前标)：\n");
	for (i = 0; i < G->vexnum; i++)
	{
		Arcnode q = G->vertices[i].firstarc->nextarc;
		while (q != NULL)
		{
			if (q->tag == '*')
			{
				printf(" %d -> ", i + 1);
				local = q->adjvex;
				break;
			}
			q = q->nextarc;
		}
	}
	printf(" %d \n\n", local+1);
}

bool TopoSort(AlGraph* G, stack T,int* ve)
{
	Stack S;
	countdegree(G);
	initStack(&S);
	initStack(T);
	int* indegree = (int*)malloc(sizeof(int) * G->vexnum);
	//printf("拓扑排序为:\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		ve[i] = 0;															//事件最早发生时间赋值为零
		indegree[i] = G->vertices[i].Endegree;
		if (G->vertices[i].Endegree == 0)
			pushStack(&S, i);
	}																		//入度为零入栈
	int count = 0;
	while (S.bottom != S.top)
	{
		int local = popStack(&S);											//存入入度为零的位置
		pushStack(T, local);
		//printf("%d ", local + 1);
		count++;
		Arcnode q = G->vertices[local].firstarc->nextarc;
		while (q != NULL)
		{
			if (ve[local] + q->info > ve[q->adjvex])
				ve[q->adjvex] = ve[local] + q->info;
			indegree[q->adjvex]--;
			if (indegree[q->adjvex] == 0)
				pushStack(&S, q->adjvex);
			q = q->nextarc;
		}
	}
	if (count == G->vexnum)
		return true;
	else
		return false;
}


void Toposort(AlGraph* G)
{
	Stack S;
	countdegree(G);
	initStack(&S);
	int* indegree = (int*)malloc(sizeof(int) * G->vexnum);
	printf("拓扑排序为:\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		indegree[i] = G->vertices[i].Endegree;
		if (G->vertices[i].Endegree == 0)
			pushStack(&S, i);
	}																		//入度为零入栈
	int count = 0;
	while (S.bottom != S.top)
	{
		int local=popStack(&S);												//存入入度为零的位置
		printf("%d ", local+1);
		count++;
		Arcnode q = G->vertices[local].firstarc->nextarc;
		while (q != NULL)
		{
			indegree[q->adjvex]--;
			if (indegree[q->adjvex] == 0)
				pushStack(&S, q->adjvex);
			q = q->nextarc;
		}
	}
}


void initStack(stack S)
{
	S->bottom = (Data*)malloc(sizeof(struct DATA));
	S->bottom->next = NULL;
	S->top = S->bottom;
}

void pushStack(stack S,int i)
{
	Data* p = (Data*)malloc(sizeof(struct DATA));
	p->data = i;
	p->next = S->top;
	S->top = p;
}

int popStack(stack S)
{
	if (S->bottom == S->top)
		return -1;										//表栈满
	Data* p;
	int i;
	p=S->top;
	i = p->data;
	S->top = p->next;
	free(p);
	return i;
}

void countdegree(AlGraph* G)
{
	for (int j = 0; j < G->vexnum; j++)
		G->vertices[j].Endegree = 0;
	for (int i = 0; i < G->vexnum; i++)
	{
		Arcnode q = G->vertices[i].firstarc->nextarc;
		while (q != NULL)
		{
			G->vertices[q->adjvex].Endegree++;
			q = q->nextarc;
		}
	}
}

void creat_graph(AlGraph* G)
{
	FILE* fp = fopen("matrix.txt", "r+");
	fscanf(fp, "%d", &G->kind);													//默认为无向图
	fscanf(fp, "%d", &G->vexnum);
	fscanf(fp, "%d", &G->arcnum);												//默认该图符合图的要求
//	G->vertices = (AdjList)malloc(sizeof(struct VNode) * G->vexnum);
	int i = 0,number=0;                                                               //记录输入的顶点个数
	while (i < G->vexnum)
	{
		G->vertices[i].firstarc = (Arcnode)malloc(sizeof(struct ArcNode));
		Arcnode q = G->vertices[i].firstarc;
		fscanf(fp, "%d", &q->adjvex);
		int k = 0;
		//		fscanf(fp, "%d", &j);
		while (1)
		{
			if (fgetc(fp) == '\n' || feof(fp))
				break;
			Arcnode p = (Arcnode)malloc(sizeof(struct ArcNode));
			fscanf(fp, "%d", &p->adjvex);
			fscanf(fp, "%d", &p->info);
			p->info_number = number;
			number++;
			q->nextarc = p;
			q = p;
			k++;
			/*		if (fgetc(fp) == '\n' || feof(fp))
						break;*/
		}
		q->nextarc = NULL;
		G->vertices[i].data = k;
		k = 0;
		i++;
	}
	fclose(fp);
}