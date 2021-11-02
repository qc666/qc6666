#include <stdio.h>
#include <stdlib.h>

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

void init_stack(stack );
void push_stack(stack ,int );
void clear_stack(stack );
void traverse_stack(stack );
bool is_empty(stack );
void menu(stack );
void zhuanhuan(stack );

int main(void)
{
	Stack S;
	init_stack(&S);
	system("cls");

	menu(&S);
	system("pause");
	return 0;
}

void menu(stack s)
{
	while(1)
	{
		printf("-----------------------------------------------\n");
		printf("---------------ʮ���ƽ���ת����----------------\n");
		printf("--------------------1.��ʼ---------------------\n");
		printf("--------------------0.�˳�---------------------\n");
		printf("-----------------------------------------------\n");
		printf("���������ѡ��\n");
		int i;
		scanf("%d",&i);
		if(i==1)
		{
			zhuanhuan(s);
			system("pause");
			system("cls");
		}
		else if(i==0)
		{
			printf("�����˳���\n");
			return;
		}
		else
		{
			printf("����������������!\n");
			system("pause");
			system("cls");
		}
	}
}

void zhuanhuan(stack s)
{
	int number,i,j;
	printf("��ҪתΪ�����ƣ�\n");
	scanf("%d",&i);
	printf("��������Ҫ����ת��������ʮ���ƣ���\n");
	scanf("%d",&number);
	j=number;
	while(number!=0)
	{
		push_stack(s,number%i);
		number/=i;
	}
	printf("10����ת��%d�������\n\n%d ---> ",i,j);
	traverse_stack(s);
	putchar(10);
	putchar(10);
	clear_stack(s);
}

void traverse_stack(stack s)
{
	if(is_empty(s))
	{
		printf("��ջ���޷�������ջ��\n\n");
		return;
	}
	node p=s->ptop;
	while(p->next)
	{
		printf("%d",p->data);
		p=p->next;
	}
}

bool is_empty(stack s)
{
	if(s->ptop==s->pbottom)
		return true;
	else
		return false;
}

void clear_stack(stack s)
{
	if(is_empty(s))
	{
		printf("��ջ���޷����ջ��\n\n");
		return;
	}
	node q,p=s->ptop;
	while(p->next!=NULL)
	{
		q=p;
		p=p->next;
		free(q);
	}
	s->ptop=s->pbottom;
	printf("ջ����գ�\n\n\n");
}

void init_stack(stack s)
{
	s->ptop=(node)malloc(sizeof(struct NODE));
	if(!s->ptop)
	{
		printf("��̬�ڴ�����ʧ�ܣ������˳���\n");
		exit(-1);
	}
	s->ptop->next=NULL;
	s->pbottom=s->ptop;
	printf("ջ�ѳɹ�������\n\n");
}

void push_stack(stack s,int num)
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
