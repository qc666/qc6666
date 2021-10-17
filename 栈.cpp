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
		printf("		----------------1.压    栈--------------\n");
		printf("		----------------2.出    栈--------------\n");
		printf("		----------------3.清 空 栈--------------\n");
		printf("		----------------4.遍 历 栈--------------\n");
		printf("		----------------5.输出栈顶--------------\n");
		printf("		----------------0.退    出--------------\n");
		printf("		-------------------end------------------\n");
		printf("		----------------------------------------\n");
		printf("请输入选择：\n");
		int i;
		scanf("%d",&i);
		if(i==1)
		{
			printf("请输入压入栈的元素:\n");
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
			printf("已退出菜单!\n\n");
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
			printf("输入有误，需重新输入!\n");
			system("pause");
			system("cls");
		}
	}
}

void traverse_stack(stack s)
{
	if(is_empty(s))
	{
		printf("空栈，无法遍历该栈！\n\n");
		return;
	}
	node p=s->ptop;
	while(p->next)
	{
		printf("栈中元素为:%d\n",p->data);
		p=p->next;
	}
}

void init_stack(stack s)
{
	s->ptop=(node)malloc(sizeof(struct NODE));
	if(!s->ptop)
	{
		printf("动态内存申请失败，程序退出！\n");
		exit(-1);
	}
	s->ptop->next=NULL;
	s->pbottom=s->ptop;
	printf("栈已成功创建！\n\n");
}

void push_stack(stack s,int num)
{
	node pnew=(node)malloc(sizeof(struct NODE));
	if(!pnew)
	{
		printf("动态内存申请失败，程序退出！\n");
		exit(-1);
	}
	pnew->data=num;
	pnew->next=s->ptop;
	s->ptop=pnew;
	printf("成功压入栈中！\n\n");
}

void pop_stack(stack s,int* number)
{
	if(is_empty(s))
	{
		printf("空栈，无法出栈！\n\n");
		return;
	}
	node pnew=s->ptop;
	*number=pnew->data;
	s->ptop=s->ptop->next;
	free(pnew);
	printf("出栈成功!\n");
	printf("出栈的元素为：%-3d\n\n",*number);
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
		printf("空栈！\n\n");
		return;
	}
	*number=s->ptop->data;
	printf("栈顶元素为：%-3d\n",*number);
}

void clear_stack(stack s)
{
	if(is_empty(s))
	{
		printf("空栈，无法清空栈！\n\n");
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
	printf("栈已清空！\n\n\n");
}