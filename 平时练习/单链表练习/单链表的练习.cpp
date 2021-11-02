#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

typedef struct LINK{
	int data;
	struct LINK* next;
}*link;

link createlink(link );
void outlink(link );
void menu(link );
void deletelink(link );
void findlink(link );
void insertlink(link );
void deletelink1(link );
void deletelink2(link );
int puanduan(link ,int );
int link_length(link );
void findlink1(link );
void findlink2(link );
void turnlink(link );
int panduan2(link ,link );
bool is_empty(link );
void sortlink(link );
link comparelink(link );

int main(void)
{
	link phead=(link)malloc(sizeof(struct LINK));
	phead=createlink(phead);
	outlink(phead);
	system("pause");
	system("cls");
	menu(phead);
	system("pause");
	return 0;
}

link createlink(link phead)
{
	link pend,body;
	phead=(link)malloc(sizeof(struct LINK));
	pend=phead;
	int length,i=0;
	printf("请输入链表长度：\n");
	scanf("%d",&length);
	srand(time(NULL));
	while(i<length)
	{
		body=(link)malloc(sizeof(LINK));
		body->data=rand()%101;
		pend->next=body;
		pend=body;
		i++;
	}
	pend->next=NULL;							//尾插			
	printf("链表创建成功！\n\n");
/*	phead->next=NULL;
	int length,i=0;
	printf("请输入链表长度：\n");
	scanf("%d",&length);
	while(i<length)
	{
		body=(link)malloc(sizeof(struct LINK));
		body->data=i+1;
		body->next=phead->next;
		phead->next=body;
		i++;
	}											//头插			*/
	return phead;
}

void outlink(link phead)
{
	link body=phead->next;
	if(body==NULL)
	{
		printf("当前为空表！\n");
		putchar(10);
		putchar(10);
		return;
	}
	int i=0;
	printf("\n----------------------------------------\n");
	printf("\n该链表的元素为：\n");
	while(body)
	{
		printf("%-6d",body->data);
		body=body->next;
		i++;
		if(i%5==0)
			putchar(10);
	}
	printf("\n----------------------------------------\n");
	putchar(10);
	putchar(10);
}

void menu(link phead)
{
	while(1)
	{
		printf("		----------------------------------------\n");
		printf("		-------------------menu-----------------\n");
		printf("		----------------1.链表插入--------------\n");
		printf("		----------------2.链表删除--------------\n");
		printf("		----------------3.链表查找--------------\n");
		printf("		----------------4.链表逆置--------------\n");
		printf("		----------------5.链表排序--------------\n");
		printf("		----------------0.退出菜单--------------\n");
		printf("		-------------------end------------------\n");
		printf("		----------------------------------------\n");
		printf("请输入选择：\n");
		int i;
		scanf("%d",&i);
		if(i==1)
		{
			insertlink(phead);
			system("pause");
			system("cls");
		}
		else if(i==2)
		{
			deletelink(phead);
			system("pause");
			system("cls");
		}
		else if(i==3)
		{
			findlink(phead);
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
			turnlink(phead);
			system("pause");
			system("cls");
		}
		else if(i==5)
		{
			sortlink(phead);
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

void insertlink(link phead)
{
	int i=0,local;
	link body=phead;
	link pnew=(link)malloc(sizeof(struct LINK));
	outlink(phead);
	link_length(phead);
	printf("请输入要插入的元素位置：\n");
	scanf("%d",&local);
	while(body&&i<local)
	{
		if(i+1==local)
			break;
		body=body->next;
		i++;
	}
	if(i>=local||!body)
	{
		printf("输入位置有误!\n");
		return;
	}
	printf("请输入要插入的元素大小:\n");
	scanf("%d",&pnew->data);
	pnew->next=body->next;
	body->next=pnew;
	outlink(phead);
}

void deletelink(link phead)
{
	if(is_empty(phead))
	{
		printf("当前为空链表，请添加元素，否则无法删除！\n");
		return;
	}
	printf("		---------------------------------------\n");
	printf("		---------------两种删除方式------------\n");
	printf("		---------------1.以元素删除------------\n");
	printf("		---------------2.以位置删除------------\n");
	printf("		---------------------------------------\n");
	printf("\n请输入你的选择:\n");
	int number;
	scanf("%d",&number);
	if(number==1)
	{
		deletelink1(phead);
	}
	else if(number==2)
	{
		deletelink2(phead);
	}
	else
	{
		printf("输入有误，重新开始删除!\n");
		deletelink(phead);
	}
}

bool is_empty(link head)
{
	if(head->next==NULL)
		return true;
	else
		return false;
}

void deletelink1(link phead)
{
	outlink(phead);
	printf("请输入需要删除的元素:\n");
	int number;
	scanf("%d",&number);
	if(puanduan(phead,number)==0)
	{
		printf("无此数!\n");
		putchar(10);
		putchar(10);
		return;
	}
	else if(puanduan(phead,number)==1)
	{
		if(phead->next->next!=NULL)
		{
			while(1)
			{
				link body=phead;
				while(body->next->data!=number && body->next->next)
					body=body->next;
				if(body->next->data!=number && NULL==body->next->next)
					break;
				if(phead->next->data==number && phead->next->next==NULL)
				{
					printf("删除的元素为%d\n",phead->next->data);
					phead->next=NULL;
					break;
				}
				link p=body->next;
				printf("删除的元素为%d\n",p->data);
				body->next=body->next->next;
				free(p);
			}
			outlink(phead);
		}
		else
		{
			printf("删除的元素为%d\n",phead->next->data);
			phead->next=NULL;
			outlink(phead);
		}
	}
}

int puanduan(link phead,int number)
{
	while(1)
	{
		link body=phead;
		while(body->next->data!=number && body->next->next)
			body=body->next;
		if(body->next->data!=number && NULL==body->next->next)
			return 0;
		else 
			return 1;
	}
}

void deletelink2(link phead)
{
	outlink(phead);
	int length=link_length(phead);
	printf("请输入需要删除的元素位置：\n");
	int local,i=1;
	scanf("%d",&local);
	link body=phead;
	if(i>local || local>length)
	{
		printf("元素位置有误！\n\n\n");
		return;
	}
	while(i<local && body->next)
	{
		body=body->next;
		i++;
	}
	link p=body->next;
	printf("删除的元素为%d\n",p->data);
	body->next=body->next->next;
	free(p);
	outlink(phead);
}

int link_length(link phead)
{
	int i=0;
	link body=phead->next;
	while(body)
	{
		body=body->next;
		i++;
	}
	printf("当前链表长度为：%d\n",i);
	putchar(10);
	return i;
}

void findlink(link phead)
{
	printf("		---------------------------------------\n");
	printf("		---------------两种查找方式------------\n");
	printf("		---------------1.以元素查找------------\n");
	printf("		---------------2.以位置查找------------\n");
	printf("		---------------------------------------\n");
	printf("\n请输入你的选择:\n");
	int number;
	scanf("%d",&number);
	if(number==1)
	{
		findlink1(phead);
	}
	else if(number==2)
	{
		findlink2(phead);
	}
	else
	{
		printf("输入有误，重新开始查找!\n");
		findlink(phead);
	}
}

void findlink1(link phead)
{
	outlink(phead);
	printf("请输入需要查找的元素:\n");
	int number,i=0,j=1;
	int arr[N];
	scanf("%d",&number);
	link body=phead->next;
	if(puanduan(phead,number)==0)
	{
		printf("无此数!\n");
		putchar(10);
		putchar(10);
		return;
	}
	else if(puanduan(phead,number)==1)
	{
		while(body)
		{
			if(body->data==number)
			{
				arr[i]=j;
				i++;
			}
			body=body->next;
			j++;
		}
	}
	int k=0;
	printf("\n该元素位置为:\n");
	while(k<i)
	{
		printf("%-3d",arr[k]);
		k++;
	}
	putchar(10);
	putchar(10);
}

void findlink2(link phead)
{
	link body=phead->next;
	int length=link_length(phead);
	printf("请输入需要查找的元素位置:\n");
	int local;
	scanf("%d",&local);
	int i=0;
	if(local<1||local>length)
	{
		printf("\n输入位置有误！\n\n\n");
		return;
	}
	while(i<local-1)
	{
		body=body->next;
		i++;
	}
	printf("\n该位置元素为：%d\n\n",body->data);
}

void turnlink(link phead)
{
	link body=phead->next,body1=body;
	link body2,pnew=phead;
	if(phead->next->next==NULL)
	{
		outlink(phead);
		return;
	}
	while(1)
	{
		while(body->next!=NULL)
		{
			body2=body;
			body=body->next;
		}
		body2->next=NULL;
		pnew->next=body;
		pnew=pnew->next;
		body=body1;
		if(body1->next==NULL)
			break;
	}
	pnew->next=body1;
	outlink(phead);
}

/*
void sortlink(link phead)
{
	link p=phead,s,r;
	link pnew=p->next,body,body1;
	while(p)
	{
		body=pnew;
		body1=body->next;
		while(body)
		{
			if(body1&&p->next->data<body1->data)
			{
				s=p->next;
				r=body->next;
				p->next=pnew->next;
				body->next=body1->next;
				r->next=p->next;
				p->next=r;
				s->next=body->next;
				body->next=s;
			}
			body1=body->next;
			body=body->next;
			pnew=p->next;
		}
		p=p->next;
		pnew=p->next;
	}
	outlink(phead);
}

  */

void sortlink(link phead)
{
	link pnew=phead;
	link body=phead;
	while(1)
	{
		link q=comparelink(body->next);
		while(body->next)
		{
			if(body->next==q)
			{
				body->next=body->next->next;
				break;
			}
			body=body->next;
		}
		q->next=pnew->next;
		pnew->next=q;
		pnew=pnew->next;
		body=pnew;
		if(pnew->next==NULL)
			break;
	}
	outlink(phead);
}

link comparelink(link phead)
{
	link body=phead;
	link s=phead;
	while(body)
	{
		if(s->data<body->data)
			s=body;
		body=body->next;
	}
	return s;
}