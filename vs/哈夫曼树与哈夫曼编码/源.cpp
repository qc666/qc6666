#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct HuffmanTree {
	int weight;
	int lchirld, rchirld, parent;
}*Huffmantree;

Huffmantree creat_Huffmantree(int ,int* );
void select(int , Huffmantree, int* , int* );
void output(Huffmantree , int);
char** creat_Huffmancode(Huffmantree ,int );
void output1(char**, int );

int main(void)
{
	char** Huffmancode;
	int w[] = { 5,29,7,8,14,23,3,11};
	Huffmantree Tree;
	Tree=creat_Huffmantree(sizeof(w)/sizeof(w[1]),w);
	output(Tree, sizeof(w) / sizeof(w[1]));
	Huffmancode=creat_Huffmancode(Tree, sizeof(w) / sizeof(w[1]));
	output1(Huffmancode, sizeof(w) / sizeof(w[1]));
	return 0;
}

void output1(char** HC,int m)
{
	printf("\n\n\t哈夫曼编码\n");
	printf("|-------|---------------|\n");
	printf("|number\t|  Huffmancode\t|\n");
	printf("|-------|---------------|\n");
	for (int i = 1; i <= m; i++)
	{
		printf("| %d\t|\t%s\t|\n",i, HC[i]);
		printf("|-------|---------------|\n");
	}
}

char** creat_Huffmancode(Huffmantree HT, int m)
{
	char** HC = (char**)malloc(sizeof(char*) * (m + 1));
	char* cd = (char*)malloc(sizeof(char) * (m+1));
	cd[m] = '\0';
	for (int i = 1; i <= m; i++)
	{
		int j = m;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchirld == c)
				cd[--j] = '0';
			else
				cd[--j] = '1';
		}
		HC[i] = (char*)malloc(sizeof(char) * (m - j));
		strcpy(HC[i], &cd[j]);
	}
	return HC;
}


Huffmantree creat_Huffmantree(int m,int* w)
{
	int n = 2 * m - 1;
	int i = 1;
	int s1, s2;
	Huffmantree HT = (Huffmantree)malloc((n + 1) * sizeof(struct HuffmanTree));
	for (i = 1; i <= m; i++)
	{
		HT[i].lchirld = 0;
		HT[i].rchirld = 0;
		HT[i].parent = 0;
		HT[i].weight = w[i - 1];
	}
	for (; i <= n; i++)
	{
		HT[i].lchirld = 0;
		HT[i].rchirld = 0;
		HT[i].parent = 0;
		HT[i].weight = 0;
	}
	output(HT, m);
	for (i = m + 1; i <= n; i++)
	{
		select(i, HT, &s1, &s2);
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchirld = s1;
		HT[i].rchirld = s2;
	}
	return HT;
}

void select(int i, Huffmantree Ht, int* min1, int* min2)
{
	int j, k;
	for (j = 1; j < i; j++)
		if (Ht[j].parent == 0)
		{
			*min1 = j;
			break;
		}
	for (k = 1; k < i; k++)
	{
		if (Ht[k].parent == 0 && j != k)
			*min2 = k;
		if (Ht[k].parent == 0 && Ht[*min1].weight > Ht[k].weight)
			*min1 = k;
	}
	for (j = 1; j < i; j++)
	{
		if (*min1!=j&&Ht[j].parent == 0 && abs(Ht[*min2].weight - Ht[*min1].weight) > abs(Ht[*min1].weight - Ht[j].weight))
			*min2 = j;
	}										//此处若不加*min1!=j，那么后续的比较过程中s1与s2相等；因为Ht[*min1].weight - Ht[j].weight等于0；
}

void output(Huffmantree HT, int i)
{
	int n = 2 * i ;
	printf("\n\n\t\t哈夫曼树\n");
	printf("|-------|-------|-------|-------|-------|\n");
	printf("|number\t|weight\t|parent\t|lchild\t|rchild\t|\n");
	printf("|-------|-------|-------|-------|-------|\n");
	for (int j = 1; j < n; j++)
	{
		printf("| %d\t| %d\t| %d\t| %d\t| %d\t|\n", j, HT[j].weight, HT[j].parent, HT[j].lchirld, HT[j].rchirld);
		printf("|-------|-------|-------|-------|-------|\n");
	}
}