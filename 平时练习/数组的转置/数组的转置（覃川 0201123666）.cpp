#include<stdio.h>
#include<stdlib.h>

#define maxsize 12500

typedef struct{
	int i,j;
	int elemtype;
}triple;


typedef struct{
	triple data[maxsize+1];
	int nu,mu,tu;
}matrix;                    //mu �У�nu �У�tu ����Ԫ����


void transposematrix(matrix ,matrix &);
void Printarry(matrix );
int panduan(int ,int ,matrix );

int main(void)
{
	matrix M,N;
	int i=1,j=1,k=1,l=0;
	printf("����������������������m n����\n");
	scanf("%d %d",&M.mu,&M.nu);
	printf("����������ʽ���и���Ԫ�أ�һ��һ�����룩��\n");
	M.tu=0;
	while(i<=M.mu*M.nu)
	{
		int elemty;
		scanf("%d",&elemty);
		l++;
		if(elemty!=0)
		{
			M.data[j].elemtype=elemty;
			M.tu++;
			M.data[j].i=k;
			M.data[j].j=l;
			j++;
		}
		if(l==M.nu)
		{
			k++;
			l=0;
		}
		i++;
	}
	printf("\n\n\nת��ǰ����Ԫλ�ã�\n");
	i=0;
	while(i<M.tu)
	{
		printf("(%d,%d,%d)\n",M.data[i+1].i,M.data[i+1].j,M.data[i+1].elemtype);
		i++;
	}                          //�����������Ԫλ�����С�Ƿ���ȷ  
	transposematrix(M,N);
	printf("\nת�ú����Ԫλ�ã�\n");
	i=0;
	while(i<N.tu)
	{
		printf("(%d,%d,%d)\n",N.data[i+1].i,N.data[i+1].j,N.data[i+1].elemtype);
		i++;
	} 
	printf("\n\n\nת��ǰ����\n");
	Printarry(M);
	printf("\nת�ú����\n");
	Printarry(N);
	system("pause");
	return 0;
}

void transposematrix(matrix M,matrix &N)
{
	N.mu=M.nu; N.nu=M.mu; N.tu=M.tu;
	int* num=(int *)malloc(sizeof(int)*(M.nu+1));
	for(int col=1;col<=M.nu;col++) 
		num[col]=0;
	for(int i=1;i<=M.tu;i++)
		num[M.data[i].j]++;
	int* copt=(int *)malloc(sizeof(int)*(M.nu+1));
	copt[1]=1;
	for(col=2;col<=M.nu;col++)
		copt[col]=copt[col-1]+num[col-1];
	int k=1;
	while(k<=M.tu)
	{
		col=M.data[k].j;
		N.data[copt[col]].j=M.data[k].i;
		N.data[copt[col]].i=M.data[k].j;
		N.data[copt[col]].elemtype=M.data[k].elemtype;
		copt[col]++;
		k++;
	}
}

void Printarry(matrix N)
{
	int i=1,j=1;
	while(i<=N.mu)
	{
		while(j<=N.nu)
		{
			int k=panduan(i,j,N);
			if(k)
				printf("%-3d",N.data[k].elemtype);
			else
				printf("%-3d",k);
			j++;
		}
		i++;
		j=1;
		putchar(10);
	}
}

int panduan(int i,int j,matrix N)
{
	int k=1;
	while(k<=N.tu)
	{
		if(i==N.data[k].i&&j==N.data[k].j)
			return k;
		k++;
	}
	return 0;
}