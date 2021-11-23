#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
	int data;
	NODE* next;
}*node;

typedef struct STACK
{
	node ptop;
	node pbottom;
}Stack,*stack;

void initstack(stack );
void pushstack(stack ,int );
void popstack(stack ,int* );
bool is_empty(stack );

int main(void)
{
	int number;
	Stack S;
	initstack(&S);
	pushstack(&S,1);
	pushstack(&S,2);
	popstack(&S,&number);
	popstack(&S,&number);
	pushstack(&S,2);
	popstack(&S,&number);
	return 0;
}

void initstack(stack s)
{
	s->ptop=(node)malloc(sizeof(struct NODE));
	if(!s->ptop)
	{
		printf("��̬�ڴ�����ʧ�ܣ������˳���\n");
		exit(-1);
	}
	s->pbottom=s->ptop;
	s->ptop->next=NULL;
}

void pushstack(stack s,int num)
{
	node pnew=(node)malloc(sizeof(struct NODE));
	if(!pnew)
	{
		printf("��̬�ڴ�����ʧ�ܣ������˳���\n");
		exit(-1);
	}
	pnew->data=num;
	pnew->next=s->ptop;
	s->ptop=pnew;
	printf("�ɹ�ѹ��ջ�У�\n\n");
}

void popstack(stack s,int* number)
{
	if(is_empty(s))
	{
		printf("��ջ���޷���ջ��\n\n");
		return;
	}
	node pnew=s->ptop;
	*number=pnew->data;
	s->ptop=s->ptop->next;
	free(pnew);
	printf("��ջ�ɹ�!\n");
	printf("��ջ��Ԫ��Ϊ��%-3d\n",*number);
}

bool is_empty(stack s)
{
	if(s->ptop==s->pbottom)
		return true;
	else
		return false;
}