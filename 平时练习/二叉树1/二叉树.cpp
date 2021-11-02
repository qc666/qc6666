#include<stdio.h>
#include<stdlib.h>

typedef struct Tree {
	char data;
	struct Tree* lchild, * rchild;
}tree;

void creat_tree(tree* );
void preodertree(tree* );

int main(void)
{
	tree* T;
	printf("�������������޺��ӵĵط��á�*����ʾ\n");
	creat_tree(T);
	printf("����������������ݣ�\n");
	preodertree(T);
	return 0;
}

void preodertree(tree* T)
{
	if(T==NULL)
		return;
	else
	{
		printf("%c",T->data);
		preodertree(T->lchild);
		preodertree(T->rchild);
		return;
	}
}

void creat_tree(tree* T)
{
	char ch;
	ch = getchar();
	if (ch == '*')
		T = NULL;
	else
	{
		T=(tree*)malloc(sizeof(tree));
		T->data = ch;
		creat_tree(T->lchild);
		creat_tree(T->rchild);
	}
}