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
	int Adjvex;								//��β
	int Info;								//Ȩֵ
}closedge;									//������ʱ��������൱�ڻ�ͷ

typedef struct linklist {
	int head;								//��β
	int rear;								//��ͷ
	int weight;								//Ȩֵ
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
	int* local1=(int*)malloc(sizeof(int)*G.vexnum);					//�洢�Ѿ��ҵ���СȨֵ�Ķ���ļ��ϴ�СΪͼ�ж������
	Arcnode q = G.vertices[0].firstarc->nextarc;
	closedge* arcs = (closedge*)malloc(sizeof(closedge) * G.vexnum);//��ʱ���飬���Դ洢ÿ�α任����Ѱ����СȨֵ
	link phead = (link)malloc(sizeof(Link));						//�������ڴ洢ÿ���ҵ���СȨֵ�ߵ���Ϣ
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
	//���±�Ϊ1�㿪ʼѰ�ң�����ʱ�����д洢���ڽӵ����Ϣ��Ȩֵ���ڽӵ���ţ�
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
		}										//Ѱ��ÿ����ʱ�����е���СȨֵ���ҵ���СȨֵ����ʱ��������
		pbody = (link)malloc(sizeof(Link));		
		pbody->rear = local;
		pbody->head = arcs[local].Adjvex;
		pbody->weight = arcs[local].Info;
		pend->pnext = pbody;
		pend = pbody;
		local1[i] = local;						//�����ö����ͬʱ����������ҵ���СȨֵ�Ķ��㼯��
		arcs[local].Info = 0;
		arcs[local].Adjvex = -1;				//�洢�ҵ�������е����ݣ���ͷ��βȨֵ�������ö�������
		q = G.vertices[local].firstarc->nextarc;//�ڸö���Ļ����ϼ���Ѱ����ö����������ڽӵ���������
		while (q != NULL)
		{				
			if (arcs[q->adjvex].Info == 0 && panduan(local1,G.vexnum, q->adjvex))
			{
				arcs[q->adjvex].Info = q->info;
				arcs[q->adjvex].Adjvex = local;
			}									//���õ��ȨֵΪ0���Ҷ��㣨��ͷ�����Ǽ���local1�е�ʱ��������ʱ����
			else if (arcs[q->adjvex].Info >= q->info && panduan(local1, G.vexnum, q->adjvex))
			{
				arcs[q->adjvex].Info = q->info;
				arcs[q->adjvex].Adjvex = local;
			}									//���õ��Ȩֵ��Ϊ0���Ҷ��㣨��ͷ�����Ǽ���local1�е�ʱ��
												//��ȨֵС����ʱ�����иö��㣨��ͷ���ıߵ�Ȩֵʱ��������ʱ����
			q = q->nextarc;
		}										// �ô�ѭ��������local�Ŷ�����ڽӵ������ʱ������
	}						//��ѭ������Ѱ����С������
	pend->pnext = NULL;
	outputlink(phead);		//����洢���������е�����
}

//panduan���������жϻ�ͷ������ʱ�������ţ��Ƿ��Ѿ����ҹ��Ķ��㣨��ͷ��,���Ƿ���true���Ƿ���false
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
						�ڴ�������ͼ�Ĺ����У�ֻ�Զ�ȡ�ļ���������һ��˵��

					1. ��һ�� ����Ϊ ͼ�����͡�������������
					2. ����һ������
						a. ��һ�����ֱ�ʾ�ڼ������㣨Ĭ�϶����±��0��ʼ��
						b. �ڶ������ֱ�ʾ�ö����м����ڽӵ�
						c. �˺� ���������ֱ�ʾ�ڽӵ���±�
								ż�������ֱ�ʾ�ڽӵ��붥���Ȩֵ
					���磺
					  0(������) 3(�ڽӵ����) 1(�ڽӵ�) 6(Ȩֵ) 2 1 3 5
  */