#include <stdio.h>
#include <stdlib.h>

void main()
{
	char str[100];
	int i=0,num1,num2,num3,num4,num5;
	num1=num2=num3=num4=num5=0;
	printf("�������ַ�����\n");
	gets(str);
	while(str[i]!='\0')
	{
		if(str[i]>='a'&&str[i]<='z')
			num1++;
		else if(str[i]>='A'&&str[i]<='Z')
			num2++;
		else if(str[i]==' ')
			num3++;
		else if(str[i]>='0'&&str[i]<='9')
			num4++;
		else if(str[i]!='\n')
			num5++;
		i++;
	}
	printf("Сд��ĸ%d������д��ĸ%d�����ո�%d��������%d��������%d��\n",num1,num2,num3,num4,num5);
}