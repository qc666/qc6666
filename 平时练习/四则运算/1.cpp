#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Opera{
	int num;
	char symbol;
	struct Opera* next;
}opera,*oper;

typedef struct Chare{
	char c;
	struct Chare * next;
}chare,*Char;

typedef struct STACK{
	Char ptop;
	Char pbottom;
}Stack,*stack;

oper chaifen(stack ,char* ,int );
void initstack(stack );
void outputlink(oper );
int panduan(stack ,char );
char panduan1(stack ,char );
void delete_brackt(oper );
int complete(oper phead);
void jisuan(oper phead);

void main()
{
	Stack S;
	oper phead;
	char* str=(char*)malloc(sizeof(char)*200);
	printf("请输入10以内四则运算(结尾加上#号)：\n");
	scanf("%s",str);
//	puts(str);
	initstack(&S);
	phead=chaifen(&S,str,strlen(str));
	jisuan(phead);
}

void initstack(stack sp)
{
	sp->ptop=(Char)malloc(sizeof(chare));
	sp->pbottom=sp->ptop;
	sp->pbottom->next=NULL;
}

void outputlink(oper phead)
{
	oper p=phead->next;
	while(p!=NULL)
	{
		if(p->num==10)
			printf("%c",p->symbol);
		else if(p->symbol=='!')
			printf("%d",p->num);
		p=p->next;
	}
	printf("\n算式拆分完毕！\n");
}

bool is_empty(stack sp)
{
	if(sp->ptop==sp->pbottom)
		return true;
	else
		return false;
}


char panduan1(stack sp,char str)
{
	if(sp->ptop->c=='+'||sp->ptop->c=='-')
	{
		if(str=='+')
			return '>';
		if(str=='-')
			return '>';
		if(str=='*')
			return '<';
		if(str=='/')
			return '<';
		if(str=='(')
			return '<';
		if(str==')')
			return '>';
	}
	else if(sp->ptop->c=='*'||sp->ptop->c=='/')
	{
		if(str=='+')
			return '>';
		if(str=='-')
			return '>';
		if(str=='*')
			return '>';
		if(str=='/')
			return '>';
		if(str=='(')
			return '<';
		if(str==')')
			return '>';
	}
	else if(sp->ptop->c=='(')
	{
		if(str=='+')
			return '<';
		if(str=='-')
			return '<';
		if(str=='*')
			return '<';
		if(str=='/')
			return '<';
		if(str=='(')
			return '<';
		if(str==')')
			return '=';
	}
	else if(sp->ptop->c==')')
	{
		if(str=='+')
			return '>';
		if(str=='-')
			return '>';
		if(str=='*')
			return '>';
		if(str=='/')
			return '>';
		if(str==')')
			return '>';
	}
}

int panduan(stack sp,char str)
{
	if(panduan1(sp,str)=='>')
		return 1;
}

oper chaifen(stack sp,char* str,int len)
{
	int i=0;
	oper phead=(oper)malloc(sizeof(opera));
	oper p=phead;
	while(i<len)
	{
		if(str[i]>'0'&&str[i]<='9')
		{
			oper body=(oper)malloc(sizeof(opera));
			body->num=str[i]-'0';
			body->symbol='!';
			p->next=body;
			p=body;
			i++;
		}
		else
		{
			Char pnew=(Char)malloc(sizeof(chare));
			pnew->c=str[i];
			pnew->next=sp->ptop;
			sp->ptop=pnew;
			i++;
			if(str[i]>'0'&&str[i]<='9')
			{
				oper body=(oper)malloc(sizeof(opera));
				body->num=str[i]-'0';
				body->symbol='!';
				p->next=body;
				p=body;
				i++;
				if(panduan(sp,str[i])==1)
				{
					Char q=sp->ptop;
					oper body=(oper)malloc(sizeof(opera));
					body->symbol=q->c;
					body->num=10;
					q=sp->ptop->next;
					sp->ptop=q;
					p->next=body;
					p=body;
				}
			}
		}
	}
	p->next=NULL;
//	printf("\n算式拆分完毕！\n");
	outputlink(phead);
	delete_brackt(phead);
//	printf("\n括号清除完毕！\n");
	return phead;
}

void delete_brackt(oper phead)
{
	oper body=phead->next;
	while(body->next!=NULL)
	{
		oper body1=body->next;
		if(body1->symbol=='('||body1->symbol==')'||body1->symbol=='.')
			body->next=body1->next;
		else
			body=body->next;
	}
	outputlink(phead);
}


void jisuan(oper phead)
{
	oper body=phead;
	int i=0;
	while(1)
	{
		oper body2=body->next->next;
		oper body1=body->next;
		if(body2->symbol=='+')
		{
			body->num=body->num+body->next->num;
			body->next=body2->next;
			body=phead->next;
		}
		else if(body2->symbol=='-')
		{
			body->num=body->num-body->next->num;
			body->next=body2->next;
			body=phead->next;
		}
		else if(body2->symbol=='*')
		{
			body->num=body->num*body->next->num;
			body->next=body2->next;
			body=phead->next;
		}
		else if(body2->symbol=='/')
		{
			body->num=body->num/body->next->num;
			body->next=body2->next;
			body=phead->next;
		}
		else
			body=body->next;
		if(body->next==NULL)
			break;
	}
	printf("%d\n",body->num);
}
