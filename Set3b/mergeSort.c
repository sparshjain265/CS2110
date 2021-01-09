/*
Program Name:	mergeSort.c
Description	: 	Set 3b: Ex1 - implementing merge sort using recursive call in ascending order
Programmer	:	Sparsh Jain
Roll No		: 	111601026
Date			: 	September 12, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Function Declarations
int * mergeSort(int *a, int n);				//Function to merge-sort a given integer array in ascending order
int * merge(int *x, int *y, int a, int b);//Function to merge 2 sorted integer arrays into 1 sorted integer array (ascending order)

int main()
{
	int *a, n, i, left, right;

	printf("\n Enter n: ");
	scanf(" %d", &n);	
	a = (int *)calloc(n, sizeof(int));		//Allocating only required amount of memory as array

	//Taking input from the user
	for(i = 0; i < n; i++)
	{
		printf("\n Enter data #%d: ", i+1);
		scanf(" %d", &a[i]);
	}
	
	//Calling function mergeSort to sort the given integer array
	a = mergeSort(a, n);
	
	//Printing the sorted list
	printf("\n Sorted List: ");
	for(i = 0; i < n; i++)
		printf(" %d", a[i]);
	
	//Freeing the dynamically allocated memory to prevent memory leak
	free(a);
	
	printf("\n\n");
	return 0;
}

//Function to merge-sort a given integer array in ascending order
//Takes pointer to the array and length of array as arguements
//Returns sorted array
int * mergeSort(int *a, int n)
{
	int *x, *y, i;
	
	//If length of the array is 1, it is already sorted
	if(n == 1)	return a;
	
	//Allocating only required amount of memory as array
	x = (int *)calloc(n/2, sizeof(int));
	y = (int *)calloc(n - n/2, sizeof(int));	
	
	//Dividing the given array into 2
	for(i = 0; i < n/2; i++)
		x[i] = a[i];
	for(; i < n; i++)
		y[i - n/2] = a[i];
	
	//Freeing the dynamically allocated memory to prevent memory leak
	free(a);
		
	//Recursive call to self to sort each division individually
	x = mergeSort(x, n/2);
	y = mergeSort(y, n - n/2);

	
	//Merging the 2 individually sorted parts, and returning the sorted array
	return merge(x, y, n/2, n - n/2);	
	
}

//Function to merge 2 sorted integer arrays into 1 sorted integer array (ascending order)
//Takes pointers to both the arrays and their lengths as arguements
//Returns sorted-merged array
int * merge(int *x, int *y, int a, int b)
{
	int *c, i = 0, j = 0;
	
	c = (int *)calloc(a + b, sizeof(int));	//Allocating only required amount of memory as array
	
	while(i < a && j < b)						//If there are elements in both the arrays, adding the smaller to the new array
	{
		if(x[i] < y[j])
			c[i+j] = x[i++];
		else 
			c[i+j] = y[j++];
	}
	//Once either of the array is empty, adding the rest of the elements to the new array
	while(i < a)									
		c[i+j] = x[i++];
	while(j < b)
		c[i+j] = y[j++];
	
	//Freeing the dynamically allocated memory to prevent memory leak
	free(x);
	free(y);
	
	//Returning the merged-sorted array
	return c;	
}

