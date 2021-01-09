/*
Program Name:	bubbleSort.c
Description	: 	Bubble Sort implementation to sort an integer array in descending order
Programmer	:	Sparsh Jain
Roll No		: 	111601026
Date			: 	September 12, 2017
*/

#include<stdio.h>
#include<stdlib.h>

void bubbleSort(int *a, int n);	//Function to sort an integer array in descending order using Bubble Sort algorithm

int main()
{
	int *a, n, i, left, right;

	printf("\n Enter n: ");
	scanf(" %d", &n);	
	a = (int *)calloc(n, sizeof(int));	//Allocating only the required amount of memory as array
	
	//Taking data from the user
	for(i = 0; i < n; i++)
	{
		printf("\n Enter data #%d: ", i+1);
		scanf(" %d", &a[i]);
	}
	
	//Function call to sort the array
	bubbleSort(a, n);
	
	//Printing the sorted array
	printf("\n Sorted List: ");
	for(i = 0; i < n; i++)
		printf(" %d", a[i]);
	
	//Freeing the dynamically allocated memory to prevent memory leak
	free(a);
	
	printf("\n\n");
	return 0;
}

//Function to sort an integer array in deccending order using Bubble Sort algorithm
//Takes a pointer to the array, and length of the array as input
void bubbleSort(int *a, int n)
{
	int i, j, tmp;
	
	//The List gets sorted in n-1 iterations of bubbling
	for(i = 0; i < n-1; i++)
	{
		//Each iteration of bubbling is 1 less than previous because the largest element is already at the end
		for(j = 0; j < n-i-1; j++)
		{
			//If an element is larger than it's next element, swapping them
			if(a[j] < a[j+1])		//Change the sign for ascending order
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}
