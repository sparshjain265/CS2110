/*
Program Name: Ex2.c
Description	: Finds the smallest element in an array (Using recursion)
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: August 22, 2017
*/

#include <stdio.h>

//Function small finds the smallest element in an integer array, takes array and number of elements as input
int small(int *a, int n);

int main()
{
	int a[10], i;
	
	//taking data from the user
	for(i = 0; i < 10; i++)
	{	
		printf("\n Enter data #%d: ", i+1);
		scanf(" %d", &a[i]);
	}
	
	//Printing the smallest element using the function small
	printf("\n Smallest value in your list is %d.", small(a, 10));
	
	printf("\n\n");
	return 0;
}

//Defining the function small
int small(int *a, int n)
{
	//taking s1 as the nth element of the array
	int s1 = a[n-1], s2;
	//if it is the only element, returning it as the smallest
	if(n == 1)
		return a[0];
	//if not, taking the smallest element till (n-1)th term in s2 using recursion
	s2 = small(a, n-1);
	//returning the smaller of the two
	return (s1 < s2 ? s1 : s2);
}
