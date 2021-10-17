#include<stdio.h>
#include<stdlib.h>

#define maxsize 12500

typedef struct {
	int i,j;
	int elemtype;
}triple;

typedef struct {
	triple data[maxsize+1];
	int* rops;
	int mu,nu,tu;
}matrix;

void scanfmatrix(matrix& );
void Printarry(matrix );
int panduan(int ,int ,matrix );  
void inputtrops(matrix& ); 
void multmatrix(matrix ,matrix ,matrix& );                 

int main(void)
{
	matrix M,N,Q;
	printf("输入前一矩阵内容:\n\n");
	scanfmatrix(M);
	system("cls");
	printf("输入后一矩阵内容:\n\n");
	scanfmatrix(N);
	system("cls");
	printf("\n\n输入矩阵呈现（按顺序输出）：\n\n\n");
	printf("前一矩阵:\n");
	Printarry(M);
	printf("\n\n后一矩阵:\n");
	Printarry(N);
	system("pause");
	inputtrops(M);
	inputtrops(N);
	multmatrix(M,N,Q);
	printf("\n\n\n相乘后矩阵为：\n");
	Printarry(Q);
	system("pause");
	return 0;
}

void multmatrix(matrix M,matrix N,matrix& Q)
{
	if(M.nu!=N.mu)
	{
		printf("行与列不对应，无法相乘!\n");
		return;
	}
	Q.mu=M.mu;
	Q.nu=N.nu;
	Q.tu=0;
	Q.rops=(int *)malloc(sizeof(int)*M.mu*M.nu);
	int brow,bcol,tp,t;
	if(M.tu*N.tu!=0)
	{
		int* ctemp=(int *)malloc(sizeof(int)*(N.nu+1));
		for(int arow=1;arow<=M.mu;arow++)
		{
			for(int i=0;i<=N.nu;i++)
				ctemp[i]=0;
			Q.rops[arow]=Q.tu+1;
			if(arow<M.mu)
				tp=M.rops[arow+1];
			else
				tp=M.tu+1;
			for(int p=M.rops[arow];p<tp;p++)
			{
				brow=M.data[p].j;
				if(brow<N.mu)
					t=N.rops[brow+1];
				else
					t=N.tu+1;
				for(int q=N.rops[brow];q<t;q++)
				{
					bcol=N.data[q].j;
					ctemp[bcol]+=N.data[q].elemtype*M.data[p].elemtype;
				}
			}
			for(bcol=1;bcol<=Q.nu;bcol++)
			{
				if(ctemp[bcol])
				{
					Q.tu++;
					if(Q.tu>maxsize)
						return;
					Q.data[Q.tu].elemtype=ctemp[bcol];
					Q.data[Q.tu].i=arow;
					Q.data[Q.tu].j=bcol;
				}
			}
		}
	}
}

void inputtrops(matrix& M)
{
	M.rops=(int *)malloc(sizeof(int)*(M.mu+1));
	int* num=(int *)malloc(sizeof(int)*(M.mu+1));
	for(int row=1;row<=M.mu;row++)
		num[row]=0;
	for(int t=1;t<=M.tu;t++)
		num[M.data[t].i]++;
	M.rops[1]=1;
	for(row=2;row<=M.mu;row++)
		M.rops[row]=M.rops[row-1]+num[row-1];
}

void scanfmatrix(matrix& M)
{
	int i=1,j=1,k=1,l=0;
	printf("请输入矩阵的行数与列数（m n）：\n");
	scanf("%d %d",&M.mu,&M.nu);
	printf("请输入行列式各行各列元素（一个一个输入）：\n");
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