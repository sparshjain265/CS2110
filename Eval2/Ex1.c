/*
Program Name: Ex1.c
Description	: Prints Fibonacci Series upto a given number (Using recursion)
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: August 22, 2017
*/

#include <stdio.h>

//Function Declaration, returns the nth fibonacci number, takes n as input
int fibonacci(int n);

int main()
{
	int i, n;
	
	//Asking the user for the number of terms
	printf("\n Enter the number of Fibonacci terms you want: ");
	scanf("%d", &n);
	
	//Loop to print n fibonacci numbers
	for(i = 0; i < n; i++)
		printf(" %d,", fibonacci(i)); //Function call inside printf statement
	printf("\b.");							//Formatting to replace the last comma with a full stop 
	
	printf("\n\n");
	return 0;
}

//Function Definition to return nth fibonacci number
int fibonacci(int n)
{	
	//If n is less than 0, returning an error message
	if(n < 0)
	{
		printf("\n Error. Negative Terms not allowed.");
		return -1;
	}
	//returning 1st and 2nd term of the series
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;
	return fibonacci(n-1) + fibonacci(n-2);	//returning nth fibonacci term using recursion
}
