#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

typedef struct BiTHrNODE{
	char data;
	struct BiTHrNODE* lchild;
	struct BiTHrNODE* rchild;
	int ltag, rtag;
}*bithrnode;

static bithrnode pre;

bithrnode THreading(bithrnode );
bithrnode creat_tree();
void InTHreading(bithrnode );
void midtree(bithrnode );

int main(void)
{
	bithrnode T,Th;
	printf("先序输入树，无孩子的地方用‘#’表示\n");
	T = creat_tree();
	printf("\n\n该树线索化中.........\n");
	Sleep(3 * 1000);
	Th=THreading(T);
	printf("\n中序输出该线索二叉树：\n");
	midtree(Th);
	putchar(10);
	return 0;
}

void midtree(bithrnode th)
{
	bithrnode P = th->lchild;
	while (P != th)
	{
		  while (P->ltag == 0)
			  P = P->lchild;
		  printf("%c", P->data);
		  while (P->rtag == 1 && P->rchild != th)
		  {
			  P = P->rchild;
			  printf("%c", P->data);
		  }
		  P = P->rchild;
	}
}

bithrnode creat_tree()
{
	char ch;
	bithrnode T;
	ch = getchar();
	if (ch == '#')
		T = NULL;
	else
	{
		T = (bithrnode)malloc(sizeof(struct BiTHrNODE));
		T->data = ch;
		T->lchild = creat_tree();
		T->rchild = creat_tree();
	}
	return T;
}

bithrnode THreading(bithrnode T)
{
	bithrnode Th = (bithrnode)malloc(sizeof(struct BiTHrNODE));
	Th->rtag = 1;
	Th->ltag = 0;
	Th->rchild = Th;
	if (T == NULL)
		Th->lchild = Th;
	else
	{
		Th->lchild = T;
		pre = Th;
		InTHreading(T);
		pre->rchild = Th;
		pre->rtag = 1;
		Th->rchild = pre;
	}
	return Th;
}

void InTHreading(bithrnode Th)
{
	if (Th == NULL)
		return;
	else
	{
		InTHreading(Th->lchild);
		if (Th->lchild == NULL)
		{
			Th->ltag = 1;
			Th->lchild = pre;
		}
		else
			Th->ltag = 0;
		if (pre->rchild == NULL)
		{
			pre->rtag = 1;
			pre->rchild = Th;
		}
		if (Th->rchild != NULL)
			Th->rtag = 0;
		pre = Th;
		InTHreading(Th->rchild);
	}
}