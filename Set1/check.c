#include<stdio.h>
int main()
{
	int *a, *b, c, d;
	c = 10;
	d = 20;
	a = &c;
	b = &d;
	if(a == b)
		printf("Both a and b point to same variable");
	else
		printf("They point to different variables");
	return 0;
}
