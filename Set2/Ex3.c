/*
Program Name: Ex3.c
Description	: Print numbers from n to 0 (Using recursion)
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: August 22, 2017
*/

#include<stdio.h>

//Function print, takes input n, prints numbers from n to 0
void print(int n);

int main()
{
	int n;
	
	//taking n from the user
	printf("Enter n: ");
	scanf(" %d", &n);
	
	//printing numbers from n to 0 using function print
	print(n);
		
	printf("\n \n");
	return 0;
}

//Defining function print
void print(int n)
{	
	// If n is less than 0, printing an error message
	if(n < 0)
	{
		printf("\n Invalid Entry!");
		return;
	}
	//Printing n
	printf("\n %d", n);
	//if n is 0, returning from the function
	if(n == 0)
		return;
	//Else printing n-1 using recursion
	print(n-1);	
}
