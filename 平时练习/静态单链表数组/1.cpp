#include <stdio.h>
#include <stdlib.h>

typedef struct ARR{
	int *pbase;
	int length;
	int cnt;
}Arr;

void init_link(Arr *arr,int len);
bool full_link(Arr* arr);
bool empty_link(Arr* arr);
void input_link(Arr* arr,int val);
void output_link(Arr *arr);
void insert_link(Arr*,int,int);
void delete_link(Arr* arr,int local);

void main()
{
	Arr arr;
	init_link(&arr,6);               //��ʼ���õ�����,Ҳ���������������
//	full_link(&arr);				 //�������Ƿ���
//	empty_link(&arr);				 //�������Ƿ��

	input_link(&arr,2);			     //������ֵ	
	input_link(&arr,3);	
//	output_link(&arr);               //���������Ԫ��
	insert_link(&arr,1,6);           //λ��2��ʾ����λ�ã�λ��3��ʾ����Ԫ��ֵ
	insert_link(&arr,1,9);  
	insert_link(&arr,1,8);  
	insert_link(&arr,1,7);  
	output_link(&arr);
	putchar(10);
	delete_link(&arr,5);             //ɾ������ĳ��λ��Ԫ�أ�λ��2��ʾ��Ҫɾ����Ԫ��λ�ã�
	output_link(&arr);
}

void init_link(Arr *arr,int len)
{
	arr->pbase=(int *)malloc(sizeof(int)*len);
	if(arr->pbase==NULL)
	{
		printf("��̬�ڴ�����ʧ�ܣ������˳���\n");
		exit(-1);
	}
	arr->length=len;
	arr->cnt=0;
}

bool full_link(Arr* arr)
{
	if(arr->length==arr->cnt)
		return true;
	else
		return false;
}

bool empty_link(Arr* arr)
{
	if(arr->cnt==0)
		return true;
	else 
		return false;
}

void input_link(Arr* arr,int val)
{
	if( full_link(arr) )
	{
		printf("link is full!!\n");
		return;
	}
	else
	{
		arr->pbase[arr->cnt]=val;
		arr->cnt++;
	}
}

void output_link(Arr *arr)
{
	if(empty_link(arr))
	{
		printf("������û��Ԫ��\n");
		return ;
	}
	for(int i=0;i<arr->cnt;i++)
		printf("%d ",arr->pbase[i]);
}

void insert_link(Arr* arr,int local,int val)
{
	if(full_link(arr))
	{
		printf("link is full!!\n");
		return;
	}
	if(local>arr->length)
	{
		printf("��ֵ���󣬵�ǰ������Ϊ %d,�ܳ���Ϊ %d\n",arr->cnt,arr->length);
		return;
	}
	else if(local>=arr->cnt)
	{
		arr->pbase[arr->cnt]=val;
		arr->cnt++;
	}
	else if(local<arr->cnt)
	{
		for(int i=arr->cnt;i>=local;i--)
			arr->pbase[i]=arr->pbase[i-1];
		arr->pbase[local-1]=val;
		arr->cnt++;
	}
}

void delete_link(Arr* arr,int local)
{
	if(empty_link(arr))
	{
		printf("link is empty!!\n");
		return;
	}
	if(local>arr->cnt)
	{
		printf("��λ��û��Ԫ��\n");
		return;
	}
	else
	{
		for(int i=local;i<arr->cnt;i++)
			arr->pbase[i-1]=arr->pbase[i];
		arr->cnt--;
	}
}
