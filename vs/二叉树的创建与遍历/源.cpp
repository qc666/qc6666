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
	printf("先序输入树，无孩子的地方用‘#’表示\n");
	T=creat_tree();
	printf("\n先序输出该树的内容：\n");
	preodertree(T);
	printf("\n\n中序输出该树的内容：\n");
	midodertree(T);
	printf("\n\n后序输出该树的内容：\n");
	succodertree(T);
	putchar(10);
	leaf_number(T);
	printf("\n该树的叶子总数为：%d\n", leaf_number(T));
	printf("\n该树的深度为：%d\n", deapthtree(T));
	putchar(10);
	M=mirror_tree(T);
	printf("\n中序输出镜像树的内容：\n");
	midodertree(M);
	putchar(10);
	system("pause");
	return 0;
}

//镜像树
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

//树的深度
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

//计算树的叶子数量
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

//后序输出
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

//中序输出
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

//先序输出
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

//创建二叉树
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