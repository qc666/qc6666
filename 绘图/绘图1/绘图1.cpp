#include <stdio.h>
#include <graphics.h>

int main()
{
	initgraph(640,480);
	bar3d(200,200,360,100,50,2);
	getchar();
	closegraph();
	return 0;
}