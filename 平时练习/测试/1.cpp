#include<stdio.h>

void main()
{
	int i,j,k,m=0,n;
	scanf("%d",&n);
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
			for(k=0;k<=n;k++)
				if(3*i+2*j+k==50&&i+j+k==n)
				{
					printf("%d %d %d\n",i,j,k);
					m++;
				}
	printf("%d\n",m);
}