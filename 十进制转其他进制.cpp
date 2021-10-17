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
		printf("---------------十进制进制转换器----------------\n");
		printf("--------------------1.开始---------------------\n");
		printf("--------------------0.退出---------------------\n");
		printf("-----------------------------------------------\n");
		printf("请输入你的选择：\n");
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
			printf("程序退出！\n");
			return;
		}
		else
		{
			printf("输入有误，重新输入!\n");
			system("pause");
			system("cls");
		}
	}
}

void zhuanhuan(stack s)
{
	int number,i,j;
	printf("需要转为几进制：\n");
	scanf("%d",&i);
	printf("请输入需要进制转换的数（十进制）：\n");
	scanf("%d",&number);
	j=number;
	while(number!=0)
	{
		push_stack(s,number%i);
		number/=i;
	}
	printf("10进制转换%d进制完成\n\n%d ---> ",i,j);
	traverse_stack(s);
	putchar(10);
	putchar(10);
	clear_stack(s);
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
