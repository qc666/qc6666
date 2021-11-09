#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct CHAR {
	char byte;
	struct CHAR* next;
}*Char;

typedef struct STACKCHAR {
	Char top;
	Char bottom;
}Stackchar;

typedef struct DATA {
	double data;
	struct DATA* next;
}*Data;

typedef struct STACKDATA {
	Data top;
	Data bottom;
}StackData;

void creat_stacksd(StackData* );
void creat_stacksc(Stackchar* );
void Enstacksd(StackData* ,double );
void Enstacksc(Stackchar* ,char );
void Outstacksd(StackData* ,double* );
void Outstacksc(Stackchar* ,char* );
void arithmetic(StackData* , Stackchar* );
bool empty_stacksd(StackData* );
bool empty_stacksc(Stackchar* );
double top_stacksd(StackData* );
char top_stacksc(Stackchar* );
char puanduanchar(char , char );
double operate(double , double , char );

int main(void)
{
	StackData D;
	Stackchar C;
	creat_stacksd(&D);
	creat_stacksc(&C);
	Enstacksc(&C,'#');
	printf("请输入四则运算（末尾以#结束）\n");
	arithmetic(&D, &C);
	printf("结果： %.3lf\n", top_stacksd(&D));
	system("pause");
	return 0;
}

void arithmetic(StackData* D, Stackchar* C)
{
	char ch=getchar(),comparechar,unusechar,meticchar;
	double a, b;
	while (ch!='#'|| top_stacksc(C) != '#')
	{
		if (ch >='0' && ch <= '9')
		{
			Enstacksd(D, ch - '0');
			ch = getchar();
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#')
		{
			if (top_stacksc(C) != '!')
			{
				comparechar = top_stacksc(C);
				switch (puanduanchar(comparechar, ch))
				{
					case '<':
						Enstacksc(C, ch);
						ch = getchar();
						break;
					case '=':
						Outstacksc(C,&unusechar);
						ch = getchar();
						break;
					case '>':
						Outstacksd(D, &a);
						Outstacksd(D, &b);
						Outstacksc(C, &meticchar);
						Enstacksd(D, operate(a, b, meticchar));
						break;
				}
			}
		}
		else
		{
			printf("输入有误，程序退出 !\n");
			exit(-1);
		}
	}
}

double operate(double a, double b, char meticchar)
{
	if (meticchar == '+')
		return a + b;
	if (meticchar == '-')
		return b - a;
	if (meticchar == '*')
		return a * b;
	if (meticchar == '/')
	{
		if (a != 0)
			return b / a;
		else
		{
			printf("被除数为0，程序退出！\n");
			exit(-1);
		}
	}
}

char puanduanchar(char ch1, char ch2)
{
	if (ch1 =='-' || ch1 == '+')
	{
		if (ch2 == '*' || ch2 == '/' || ch2 == '(')
			return '<';
		else
			return '>';
	}
	else if (ch1 == '*' || ch1 == '/')
	{
		if (ch2 == '(')
			return '<';
		else
			return '>';
	}
	else if (ch1 == '(')
	{
		if (ch2 == ')')
			return '=';
		else if (ch2 != '#')
			return '<';
	}
	else if (ch1 == ')')
	{
		if (ch2 != '(')
			return '>';
	}
	else if (ch1 == '#')
	{
		if (ch2 != ')' && ch2 != '#')
			return '<';
		else if (ch2 == '#')
			return '=';
	}
}

double top_stacksd(StackData* D)
{
	if (empty_stacksd(D))
		return 0;
	else
		return D->top->data;
}

char top_stacksc(Stackchar* C)
{
	if (empty_stacksc(C))
		return '!';
	else
		return C->top->byte;
}

bool empty_stacksd(StackData* D)
{
	if (D->top == D->bottom)
		return true;
	else
		return false;
}

bool empty_stacksc(Stackchar* C)
{
	if (C->top == C->bottom)
		return true;
	else
		return false;
}

void Outstacksd(StackData* D,double* i)
{
	if (D->top == D->bottom)
		return;
	Data q;
	q=D->top;
	*i = q->data;
	D->top = D->top->next;
	free(q);
}

void Outstacksc(Stackchar* C,char* ch)
{
	if (C->top == C->bottom)
		return;
	Char q;
	q = C->top;
	*ch = q->byte;
	C->top = C->top->next;
	free(q);
}

void Enstacksd(StackData* D, double i)
{
	Data bady = (Data)malloc(sizeof(struct DATA));
	bady->data = i;
	bady->next = D->top;
	D->top = bady;
}

void Enstacksc(Stackchar* C, char ch)
{
	Char bady = (Char)malloc(sizeof(struct CHAR));
	bady->byte = ch;
	bady->next = C->top;
	C->top = bady;
}

void creat_stacksd(StackData* D)
{
	D->top = (Data)malloc(sizeof(struct DATA));
	D->top->next = NULL;
	D->bottom = D->top;
}

void creat_stacksc(Stackchar* C)
{
	C->top = (Char)malloc(sizeof(struct CHAR));
	C->top->next = NULL;
	C->bottom = C->top;
}