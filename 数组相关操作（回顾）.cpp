#include<stdio.h>
#include<stdlib.h>

typedef struct Arr{
	int length;                //表示数组长度
	int num;                 //表示数组中第几个元素
	int* a;
}Arr,*arr;
  
void init(arr);              //初始化数组
void input(arr);             //输入数组元素
void output(arr);            //输出数组元素
bool is_full(arr);           //判断数组是否满
bool is_empty(arr);          //判断数组是否空
void insert(arr);            //插入数组元素
void Delete(arr);            //删除数组元素


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

//创建该数组：
void init(arr arr1)
{
	printf("input list length:\n");
	scanf("%d",&arr1->length);
	arr1->a=(int*)malloc(sizeof(int)*arr1->length);				//创建一个动态数组
	if(arr1->a==NULL)
	{
		printf("动态内存申请失败，程序退出！\n");
		exit(-1);
	}
	arr1->num=0;
}

//输入元素
void input(arr arry)
{
	while(arry->num!=arry->length)
	{
		printf("input %d number:\n",arry->num+1);
		scanf("%d",&arry->a[arry->num]);
		arry->num++;                          //数组元素的位置往后走一个位置
	}
	if( is_full(arry) )					     //其实以此处的方式输入，数组必满，只是为了提醒输入者
		printf("the arry is full!\n");         
}

//判断数组是否满
bool is_full(arr arr1)
{
	if(arr1->num==arr1->length)
		return true;
	else
		return false;
}

//判断数组是否空
bool is_empty(arr arr1)
{
	if(arr1->num==0)
		return true;
	else
		return false;
}

/*
插入思想：
	1、当需要插入的元素在数组末尾时（也就是插入的地方没有人和元素），
	   直接在该数组末尾加上插入的元素；
	2、当需要插入的元素在数组中间时（也就是插入的地方有元素时），
	   先将该位置的原本元素往后移，再在原来需要插入的位置补上插入的元素；
	3、此处只为提醒输入者输入位置有误，不能进行再进行相关的插入操作；
    
	注：操作者在输入时输入的是元素个数的位置，故4处将减1。
*/


//插入元素位置
void insert(arr arry)
{
	if(is_full(arry))
	{
		printf("the arry is full!\n");
		return;                                      //此处假设成立直接跳出该函数
	}
	int k,data;
	printf("请输入插入元素的位置：\n");
	scanf("%d",&k);
	if(k>arry->num&&k<=arry->length)				//1处
	{
		printf("请输入插入的元素：\n");
		scanf("%d",&data);
		arry->a[arry->num]=data;
		arry->num++;
		output(arry);
	}
	else if(k<=arry->num&&k>0)						//2处
	{
		printf("请输入插入的元素：\n");
		scanf("%d",&data);
		int i=arry->num;
		k-=1;										//4处
		while(i!=k)
		{
			arry->a[i]=arry->a[i-1];
			i--;
		}
		arry->a[k]=data;
		arry->num++;
		output(arry);
	}
	else                                           //3处
		printf("输入位置有误！\n");
}

//输出元素
void output(arr arry)
{
	int i=0;
	if(is_empty(arry))
	{
		printf("the arry is empty! output error\n");
		return;											//此处假设成立直接跳出该函数
	}
	printf("arry is:\n");
	while(i!=arry->num)
	{
		printf("%d ",arry->a[i]);
		i++;
	}
	putchar(10);										//另一种方式进行换行
}

/*
删除思想：
	1、此处只为将位置调回系统的默认位置（系统从0开始数，用户从1开始数）；
	2、当需要删除的元素在数组中间时（也就是删除的地方有元素时），
	   直接将该位置的原本元数往前移，等价于删除；
	3、此处其他位置均不能删除。
*/

//删除相应元素
void Delete(arr arry)
{
	if(is_empty(arry))
	{
		printf("the arry is empty!\n");
		return;
	}
	int m;
	printf("请输入删除元素的位置：\n");
	scanf("%d",&m);
	m-=1;												//1处
	if(m<arry->num&&m>=0)								//2处
	{
		int i=m+1,e;
		e=arry->a[m];
		printf("删除的元素为：%d\n",e);
		while(i<arry->num)
		{
			arry->a[i-1]=arry->a[i];
			i++;
		}
		arry->num--;
		output(arry);
	}
	else
		printf("输入位置有误！\n");						//3处
}