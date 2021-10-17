#include<stdio.h>
#include<stdlib.h>

typedef struct Arr{
	int length;                //��ʾ���鳤��
	int num;                 //��ʾ�����еڼ���Ԫ��
	int* a;
}Arr,*arr;
  
void init(arr);              //��ʼ������
void input(arr);             //��������Ԫ��
void output(arr);            //�������Ԫ��
bool is_full(arr);           //�ж������Ƿ���
bool is_empty(arr);          //�ж������Ƿ��
void insert(arr);            //��������Ԫ��
void Delete(arr);            //ɾ������Ԫ��


void main()
{
	Arr pbase;
	init(&pbase);
	input(&pbase);
	output(&pbase);
//	is_empty(&pbase);
//	is_full(&pbase);
	Delete(&pbase);
	insert(&pbase);
}

//���������飺
void init(arr arr1)
{
	printf("input list length:\n");
	scanf("%d",&arr1->length);
	arr1->a=(int*)malloc(sizeof(int)*arr1->length);				//����һ����̬����
	if(arr1->a==NULL)
	{
		printf("��̬�ڴ�����ʧ�ܣ������˳���\n");
		exit(-1);
	}
	arr1->num=0;
}

//����Ԫ��
void input(arr arry)
{
	while(arry->num!=arry->length)
	{
		printf("input %d number:\n",arry->num+1);
		scanf("%d",&arry->a[arry->num]);
		arry->num++;                          //����Ԫ�ص�λ��������һ��λ��
	}
	if( is_full(arry) )					     //��ʵ�Դ˴��ķ�ʽ���룬���������ֻ��Ϊ������������
		printf("the arry is full!\n");         
}

//�ж������Ƿ���
bool is_full(arr arr1)
{
	if(arr1->num==arr1->length)
		return true;
	else
		return false;
}

//�ж������Ƿ��
bool is_empty(arr arr1)
{
	if(arr1->num==0)
		return true;
	else
		return false;
}

/*
����˼�룺
	1������Ҫ�����Ԫ��������ĩβʱ��Ҳ���ǲ���ĵط�û���˺�Ԫ�أ���
	   ֱ���ڸ�����ĩβ���ϲ����Ԫ�أ�
	2������Ҫ�����Ԫ���������м�ʱ��Ҳ���ǲ���ĵط���Ԫ��ʱ����
	   �Ƚ���λ�õ�ԭ��Ԫ�������ƣ�����ԭ����Ҫ�����λ�ò��ϲ����Ԫ�أ�
	3���˴�ֻΪ��������������λ�����󣬲��ܽ����ٽ�����صĲ��������
    
	ע��������������ʱ�������Ԫ�ظ�����λ�ã���4������1��
*/


//����Ԫ��λ��
void insert(arr arry)
{
	if(is_full(arry))
	{
		printf("the arry is full!\n");
		return;                                      //�˴��������ֱ�������ú���
	}
	int k,data;
	printf("���������Ԫ�ص�λ�ã�\n");
	scanf("%d",&k);
	if(k>arry->num&&k<=arry->length)				//1��
	{
		printf("����������Ԫ�أ�\n");
		scanf("%d",&data);
		arry->a[arry->num]=data;
		arry->num++;
		output(arry);
	}
	else if(k<=arry->num&&k>0)						//2��
	{
		printf("����������Ԫ�أ�\n");
		scanf("%d",&data);
		int i=arry->num;
		k-=1;										//4��
		while(i!=k)
		{
			arry->a[i]=arry->a[i-1];
			i--;
		}
		arry->a[k]=data;
		arry->num++;
		output(arry);
	}
	else                                           //3��
		printf("����λ������\n");
}

//���Ԫ��
void output(arr arry)
{
	int i=0;
	if(is_empty(arry))
	{
		printf("the arry is empty! output error\n");
		return;											//�˴��������ֱ�������ú���
	}
	printf("arry is:\n");
	while(i!=arry->num)
	{
		printf("%d ",arry->a[i]);
		i++;
	}
	putchar(10);										//��һ�ַ�ʽ���л���
}

/*
ɾ��˼�룺
	1���˴�ֻΪ��λ�õ���ϵͳ��Ĭ��λ�ã�ϵͳ��0��ʼ�����û���1��ʼ������
	2������Ҫɾ����Ԫ���������м�ʱ��Ҳ����ɾ���ĵط���Ԫ��ʱ����
	   ֱ�ӽ���λ�õ�ԭ��Ԫ����ǰ�ƣ��ȼ���ɾ����
	3���˴�����λ�þ�����ɾ����
*/

//ɾ����ӦԪ��
void Delete(arr arry)
{
	if(is_empty(arry))
	{
		printf("the arry is empty!\n");
		return;
	}
	int m;
	printf("������ɾ��Ԫ�ص�λ�ã�\n");
	scanf("%d",&m);
	m-=1;												//1��
	if(m<arry->num&&m>=0)								//2��
	{
		int i=m+1,e;
		e=arry->a[m];
		printf("ɾ����Ԫ��Ϊ��%d\n",e);
		while(i<arry->num)
		{
			arry->a[i-1]=arry->a[i];
			i++;
		}
		arry->num--;
		output(arry);
	}
	else
		printf("����λ������\n");						//3��
}