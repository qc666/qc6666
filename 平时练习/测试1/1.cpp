#include<stdio.h>

int main(void)
{
	int l,a,b;
	scanf("%d %d %d",&l,&a,&b);
	int s,m=0,n=0,sum=l;
	for(int i=0;i<=l/a;i++)
	{
		for(int j=0;j<=l/b;j++)
		{
			s=l-a*i-b*j;
			if(sum>=s&&s>=0)
			{
				sum=s;
				m=i;
				n=j;
			}
		}
	}
	printf("%d %d %d\n",m,n,sum);
}