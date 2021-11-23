#include<stdio.h>
#include<stdlib.h>

int number = 0;				//ͳ����ͨͼ����

typedef struct ArcNode {
	int adjvex;							//��ָ�ĵ��λ�ã�
	struct ArcNode* nextarc;			//ָ����һ���ڽӵ㣻
	int info;							//�������Ȩ�أ�
	int info_number;					//Ȩ�����
	char tag;							//��Ƿ�ؼ����ؼ�Ϊ *�����ؼ�Ϊ�ո����
}*Arcnode;

typedef struct VNode {
	int Endegree;						//���
	int data;							//ÿ��������Ϣ��������ϸָ�������޺��ָ�룬��Ϊ0
	Arcnode firstarc;					//����
}Vnode, * AdjList;

typedef struct {
	Vnode vertices[100];
//	AdjList vertices;						//��������
	int vexnum;								//ͼ������
	int arcnum;										//ͼ����
	int kind;								//ͼ����
}AlGraph;

typedef struct DATA {
	int data;								//ջ�����Ϊ�㶥�����
	struct DATA* next;
}Data;

typedef struct STACK {
	Data* top;								//ջ��
	Data* bottom;							//ջ��
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
		printf("���������л�·�������˳�!\n");
		exit(-1);
	}
	for (int i = 0; i < G->vexnum; i++)
		vl[i] = ve[G->vexnum-1];											//�¼���ٷ���ʱ���ʼ��������Ϊȫ����ɵ�ʱ�䣩
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
	printf("�¼�\t���緢��ʱ��\t������ʱ��\t\n");
	for (i = 0; i < G->vexnum; i++)
		printf("%3d \t%5d \t\t%5d\n",i+1,ve[i],vl[i]);
	printf("\n\n�\t���緢��ʱ��\t������ʱ��\t\n");
	for (i = 0; i < G->arcnum; i++)
		printf("%3d \t%5d \t\t%5d\n", i+1 , ee[i], el[i]);
	printf("\n\n�ؼ�·��Ϊ(���¼�Ϊǰ��)��\n");
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
	//printf("��������Ϊ:\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		ve[i] = 0;															//�¼����緢��ʱ�丳ֵΪ��
		indegree[i] = G->vertices[i].Endegree;
		if (G->vertices[i].Endegree == 0)
			pushStack(&S, i);
	}																		//���Ϊ����ջ
	int count = 0;
	while (S.bottom != S.top)
	{
		int local = popStack(&S);											//�������Ϊ���λ��
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
	printf("��������Ϊ:\n");
	for (int i = 0; i < G->vexnum; i++)
	{
		indegree[i] = G->vertices[i].Endegree;
		if (G->vertices[i].Endegree == 0)
			pushStack(&S, i);
	}																		//���Ϊ����ջ
	int count = 0;
	while (S.bottom != S.top)
	{
		int local=popStack(&S);												//�������Ϊ���λ��
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
		return -1;										//��ջ��
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
	fscanf(fp, "%d", &G->kind);													//Ĭ��Ϊ����ͼ
	fscanf(fp, "%d", &G->vexnum);
	fscanf(fp, "%d", &G->arcnum);												//Ĭ�ϸ�ͼ����ͼ��Ҫ��
//	G->vertices = (AdjList)malloc(sizeof(struct VNode) * G->vexnum);
	int i = 0,number=0;                                                               //��¼����Ķ������
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