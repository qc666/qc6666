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
void pop_stack(stack ,int* );
bool is_empty(stack );
void gettop(stack ,int* );
void clear_stack(stack );
void traverse_stack(stack );
void menu(stack );

int main(void)
{
	Stack S;
	init_stack(&S);
	system("pause");
	system("cls");
	menu(&S);
	system("pause");
	return 0;
}

void menu(stack s)
{
	while(1)
	{
		int number;
		printf("		----------------------------------------\n");
		printf("		-------------------menu-----------------\n");
		printf("		----------------1.ѹ    ջ--------------\n");
		printf("		----------------2.��    ջ--------------\n");
		printf("		----------------3.�� �� ջ--------------\n");
		printf("		----------------4.�� �� ջ--------------\n");
		printf("		----------------5.���ջ��--------------\n");
		printf("		----------------0.��    ��--------------\n");
		printf("		-------------------end------------------\n");
		printf("		----------------------------------------\n");
		printf("������ѡ��\n");
		int i;
		scanf("%d",&i);
		if(i==1)
		{
			printf("������ѹ��ջ��Ԫ��:\n");
			int num;
			scanf("%d",&num);
			push_stack(s,num);
			system("pause");
			system("cls");
		}
		else if(i==2)
		{
			pop_stack(s,&number);
			system("pause");
			system("cls");
		}
		else if(i==3)
		{
			clear_stack(s);
			system("pause");
			system("cls");
		}
		else if(i==0)
		{
			printf("���˳��˵�!\n\n");
			return;
		}
		else if(i==4)
		{
			traverse_stack(s);
			system("pause");
			system("cls");
		}
		else if(i==5)
		{
			gettop(s,&number);
			system("pause");
			system("cls");
		}
		else 
		{
			printf("������������������!\n");
			system("pause");
			system("cls");
		}
	}
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
		printf("ջ��Ԫ��Ϊ:%d\n",p->data);
		p=p->next;
	}
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

void pop_stack(stack s,int* number)
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
	printf("��ջ��Ԫ��Ϊ��%-3d\n\n",*number);
}

bool is_empty(stack s)
{
	if(s->ptop==s->pbottom)
		return true;
	else
		return false;
}

void gettop(stack s,int* number)
{
	if(is_empty(s))
	{
		printf("��ջ��\n\n");
		return;
	}
	*number=s->ptop->data;
	printf("ջ��Ԫ��Ϊ��%-3d\n",*number);
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