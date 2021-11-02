#include<stdio.h>
#include<stdlib.h>

typedef struct Tree {
	char data;
	struct Tree* lchild, * rchild;
}tree;

tree* creat_tree();
void preodertree(tree * );
void midodertree(tree*);
void succodertree(tree*);
int leaf_number(tree*);
int deapthtree(tree* );
tree* mirror_tree(tree*);

int main(void)
{
	tree* T,* M;
	printf("�������������޺��ӵĵط��á�#����ʾ\n");
	T=creat_tree();
	printf("\n����������������ݣ�\n");
	preodertree(T);
	printf("\n\n����������������ݣ�\n");
	midodertree(T);
	printf("\n\n����������������ݣ�\n");
	succodertree(T);
	putchar(10);
	leaf_number(T);
	printf("\n������Ҷ������Ϊ��%d\n", leaf_number(T));
	printf("\n���������Ϊ��%d\n", deapthtree(T));
	putchar(10);
	M=mirror_tree(T);
	printf("\n������������������ݣ�\n");
	midodertree(M);
	putchar(10);
	system("pause");
	return 0;
}

//������
tree* mirror_tree(tree* T)
{
	if (T == NULL)
		return NULL;
	else
	{
		tree* Tp=(tree*)malloc(sizeof(tree));
		Tp->data = T->data;
		Tp->rchild=mirror_tree(T->lchild);
		Tp->lchild=mirror_tree(T->rchild);
		return Tp;
	}
}

//�������
int deapthtree(tree* t)
{
	if (t == NULL)
		return 0;
	if (t->lchild == NULL && t->rchild == NULL)
		return 1;
	else
	{
		if(deapthtree(t->lchild)>deapthtree(t->rchild))
			return deapthtree(t->lchild)+1;
		else
			return deapthtree(t->rchild)+1;
	}
}

//��������Ҷ������
int leaf_number(tree* T)
{
	if (T == NULL)
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
	{
		return (leaf_number(T->lchild) + leaf_number(T->rchild));
	}
}

//�������
void succodertree(tree* t)
{
	if (t == NULL)
		return;
	else
	{
		succodertree(t->lchild);
		succodertree(t->rchild);
		printf("%c", t->data);
	}
}

//�������
void midodertree(tree* t)
{
	if (t == NULL)
		return;
	else
	{
		midodertree(t->lchild);
		printf("%c", t->data);
		midodertree(t->rchild);
	}
}

//�������
void preodertree(tree* T)
{
	if (T == NULL)
		return;
	else
	{
		printf("%c", T->data);
		preodertree(T->lchild);
		preodertree(T->rchild);
		return;
	}
}

//����������
tree* creat_tree()
{
	char ch;
	tree* T;
	ch = getchar();
	if (ch == '#')
		T = NULL;
	else
	{
		T = (tree*)malloc(sizeof(tree));
		T->data = ch;
		T->lchild=creat_tree();
		T->rchild=creat_tree();
	}
	return T;
}