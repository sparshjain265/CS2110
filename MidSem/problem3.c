/*
Serial No	: B
Question No	: Q3
Program Name: problem3.c
Programmer	: Sparsh Jain
Roll No		: 111601026
IP address	: 10.64.1.168
Description	: Program to output 2 real numbers whose sum is closest to a given number (from a sorted array)
Logic			: a number is closest to the another number when the absolute value of their difference is minimum
*/

#include<stdio.h>
#include<stdlib.h>

void find(double *a, int *x, int *y, double z, int n);	//Function Declaration to find 2 real numbers in the list whose sum is closest to a given number

int main()
{
	int i = 0, n, x, y;
	double *a, e = 0.49*10E-6, z;
	
	//Asking user for n
	printf("\n Enter number of elements in your list: ");
	scanf(" %d", &n);
	
	//Allocating required memory
	a = (double *)calloc(n, sizeof(double));
	
	//Taking input
	while(i < n)
	{
		printf("\n Enter data #%d: ", i+1);
		scanf(" %lf", &a[i]);
		if(i > 0 && a[i] < a[i-1] - e)							//If data is not in ascending order, prompt the user
		{
			printf("\n Enter data greater than %lf", a[i-1]);
			continue;
		}
		i++;
	}
	
	//Taking the element from the user which we have to find as the sum of 2 numbers
	printf("\n Enter the element you want to find (closest) sum of: ");
	scanf(" %lf", &z);
	
	//Calling function find to find the index of the two numbers
	find(a, &x, &y, z, n);
	
	//Printing the output
	printf("\n Sum of %lf (at %d) and %lf (at %d) is closest to %lf.", a[x], x, a[y], y, z);
	
	//Freeing the allocated memory
	free(a);
	printf("\n\n");
	return 0;
}

//Function definition to find the index of 2 numbers whose sum is closest to the given number
//Takes pointer to the array, pointer to integer indices x & y, real number z(which we have to find as the sum) and number of elements in the array as input
//Changes the value of indices x & y such that sum of values at those indices is closest to the given number
void find(double *a, int *x, int *y, double z, int n)
{
	int i, j;
	double e = 0.49*10E-6, sum, d, t;
	
	//Initially setting x & y as first two elements
	*x = 0;
	*y = 1;
	
	//Setting initial sum condition
	sum = a[*x] + a[*y];
	d = z - sum;
	if(d < 0)
		d = -d;
		
	//Checking against other possible combinations
	for(i = 0; i < n; i++)
	{
		for(j = i+1; j < n; j++)
		{
			t = z - (a[i] + a[j]);
			if(t < 0)
				t = -t;
			if(t < d - e)	//If any other combination is closer, change the indices
			{
				*x = i;
				*y = j;
				d = t;
			}
		}
	}		
}


