# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
}NODE, * PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pBottom;
}STACK, * PSTACK;  //PSTACK �ȼ��� struct STACK *

void init(PSTACK);
void push(PSTACK, int );
void traverse(PSTACK);
bool pop(PSTACK, int *);
void clear(PSTACK pS);

int main(void)
{
	STACK S;  //STACK �ȼ��� struct Stack
	int val;

	init(&S);  //Ŀ�������һ����ջ
	push(&S, 1); //ѹջ
	push(&S, 2);
	push(&S, 3);
	push(&S, 4);
	push(&S, 5);
	push(&S, 6);
//	traverse(&S); //�������
	
//	clear(&S);
	//traverse(&S); //�������

	if ( pop(&S, &val) )
	{
		printf("��ջ�ɹ�����ջ��Ԫ����%d\n", val);
	}
	else
	{
		printf("��ջʧ��!\n");
	}

	if ( pop(&S, &val) )
	{
		printf("��ջ�ɹ�����ջ��Ԫ����%d\n", val);
	}
	else
	{
		printf("��ջʧ��!\n");
	}
	traverse(&S); //�������

	return 0;
}

void init(PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if (NULL == pS->pTop)
	{
		printf("��̬�ڴ����ʧ��!\n");
		exit(-1);
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL; //pS->Bottom->pNext = NULL;
	}
}

void push(PSTACK pS, int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	
	pNew->data = val;
	pNew->pNext = pS->pTop; //pS->Top���ܸĳ�pS->Bottom
	pS->pTop = pNew;

	return;
}

void traverse(PSTACK pS)
{
	PNODE p = pS->pTop;

	while (p != pS->pBottom)
	{
		printf("%d  ", p->data);
		p = p->pNext;
	}
	printf("\n");

	return;
}

bool empty(PSTACK pS)
{
	if (pS->pTop == pS->pBottom)
		return true;
	else
		return false;
}

//��pS��ָ���ջ��ջһ�Σ����ѳ�ջ��Ԫ�ش���pVal�β���ָ��ı����У������ջʧ�ܣ�����false,���򷵻�true
bool pop(PSTACK pS, int * pVal)
{
	if ( empty(pS) ) //pS�����ŵľ���S�ĵ�ַ
	{
		return false;
	}
	else
	{
		PNODE r = pS->pTop;
		*pVal = r->data;
		pS->pTop = r->pNext;
		free(r);
		r = NULL;

		return true;
	}
}

//clear���
void clear(PSTACK pS)
{
	if (empty(pS))
	{
		return;
	}
	else
	{
		PNODE p = pS->pTop;
		PNODE q = NULL;

		while (p != pS->pBottom)
		{
			q = p->pNext;
			free(p);
			p = q;
		}
		pS->pTop = pS->pBottom;
	}
}