#include<stdio.h>
#include<string.h>

int main(void)
{
	char name[100],old[20],new1[20];
	printf("ÇëÊäÈëĞÕÃû:\n");
	gets(name);
	printf("ÊäÈë½«±»Ìæ»»Æ¬¶Î:\n");
	gets(old);
	printf("ÊäÈëÌæ»»×Ö·û´®:\n");
	gets(new1);
	char name1[100];
	int i=0,j=0,m=0;
	while(name[i]!='\0')
	{
		if(name[i]==old[0])
		{
			while(old[m]!='\0')
			{
				if(name[i+m]!=old[m])
					break;
				m++;
			}
		}
		if(old[m]=='\0')
		{
			i=i+m;
			int t=0;
			while(new1[t]!='\0')
			{
				name1[j]=new1[t];
				j++;
				t++;
			}
			m=0;
		}
		else 
		{
			name1[j]=name[i];
			j++;
			i++;
			m=0;
		}
	}
	name1[j]='\0';
	puts(name1);
	return 0;
}