/*
Serial No	: B
Question No	: Q1
Program Name: problem1.c
Programmer	: Sparsh Jain
Roll No		: 111601026
IP address	: 10.64.1.168
Description	: Program to implement a recursive function to calculate modulo
Logic			: division is repeated subtraction! Subtract divisor from the dividend until what remains is less than the divisor. This is remainder or modulo
*/

#include<stdio.h>

int mod(int x, int y);										//Declaring function mod

int main()
{
	int x, y;
	
	//Asking the user for input
	printf("\n Enter (positive integer) x: ");
	scanf(" %d", &x);
	if(x < 0)	//Checking the validity of input
	{
		printf("\n Invalid Input! Terminating!");
		return -1;
	}
	printf("\n Enter (positive integer) y: ");
	scanf(" %d", &y);
	if(y <= 0)	//Checking the validity of input
	{
		printf("\n Invalid Input! Terminating!");
		return -1;
	}
	
	//Calling function mod to calculate the modulo and printing the output
	printf("\n %d modulo %d = %d", x, y, mod(x,y));
	
	printf("\n\n");
	return 0;
}

//Defining function mod to calculate modulo using recursion
//Takes two integers x and y as arguments
//Returns x%y 
int mod(int x, int y)
{
	if(x<y)						//If x<y x is mod
		return x;
	else return mod(x-y,y);	//Else subtract y from x and recursively call mod again
}
