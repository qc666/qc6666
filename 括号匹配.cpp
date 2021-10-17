#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
	int elm;
	NODE* next;
}*node;

typedef struct STACK
{
	node ptop;
	node pbottom;
}Stack,*stack;

void init_stack(stack );
void push_stack(stack ,char );
bool is_empty(stack );
void pop_stack(stack );
bool compare_top(stack ,char );
void peidui(stack );

int main(void)
{
	Stack S;
	init_stack(&S);
	peidui(&S);
	system("pause");
	return 0;
}

void peidui(stack s)
{
	char ch;
	printf("����������ŵ���ʽ:\n");
	while((ch=getchar())!='\n')
	{
		if(ch=='('||ch=='{'||ch=='[')
			push_stack(s,ch);
		else if(ch==')')
		{
			if(compare_top(s,ch))
				pop_stack(s);
			else
			{
				printf("���ʧ�ܣ�\n");
				return;
			}
		}
		else if(ch==']')
		{
			if(compare_top(s,ch))
				pop_stack(s);
			else 
			{
				printf("���ʧ�ܣ�\n");
				return;
			}
		}
		else if(ch=='}')
		{
			if(compare_top(s,ch))
				pop_stack(s);
			else 
			{
				printf("���ʧ�ܣ�\n");
				return;
			}
		}
	}
	if(is_empty(s))
		printf("��Գɹ���\n");
	else
		printf("���ʧ�ܣ�\n");
}

bool is_empty(stack s)
{
	if(s->ptop==s->pbottom)
		return true;
	else
		return false;
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

void push_stack(stack s,char ch)
{
	node pnew=(node)malloc(sizeof(struct NODE));
	if(!pnew)
	{
		printf("��̬�ڴ�����ʧ�ܣ������˳���\n");
		exit(-1);
	}
	pnew->elm=ch;
	pnew->next=s->ptop;
	s->ptop=pnew;
}

void pop_stack(stack s)
{
	node pnew=s->ptop;
	s->ptop=s->ptop->next;
	free(pnew);
}

bool compare_top(stack s,char ch)
{
	if(is_empty(s))
		return false;
	if(ch==')')
	{
		if(s->ptop->elm=='(')
			return true;
		else 
			return false;
	}
	if(ch==']')
	{
		if(s->ptop->elm=='[')
			return true;
		else 
			return false;
	}
	if(ch=='}')
	{
		if(s->ptop->elm=='{')
			return true;
		else 
			return false;
	}
}
