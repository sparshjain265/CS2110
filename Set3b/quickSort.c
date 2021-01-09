/*
Program Name:	quickSort.c
Description	: 	Quick-Sort implementation to sort an array of integers in Ascending Order
Programmer	:	Sparsh Jain
Roll No		: 	111601026
Date			: 	September 12, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Function Declarations
void quickSort(int *a, int left, int right);	//Function to sort a given array in ascending order using quick-sort algorithm
int part(int *a, int left, int right);			//Function to divide the given array into 2 according to the pivot element

int main()
{
	int *a, n, i;
	
	printf("\n Enter n: ");
	scanf(" %d", &n);	
	a = (int *)calloc(n, sizeof(int));			//Allocating only the required amount of memory as array

	//Taking data from the user
	for(i = 0; i < n; i++)
	{
		printf("\n Enter data #%d: ", i+1);
		scanf(" %d", &a[i]);
	}	
	
	//Function call to sort the array
	quickSort(a, 0, n-1);
	
	//Printing the sorted list
	printf("\n Sorted List: ");
	for(i = 0; i < n; i++)
		printf(" %d", a[i]);
	
	//Freeing the dynamically allocated memory to prevent memory leakage
	free(a);
	
	printf("\n\n");
	return 0;
}

//Function to sort a given array in ascending order using quick-sort algorithm
//Takes a pointer to the array, and left and right pointers as input
void quickSort(int *a, int left, int right)
{
	int partition;
	
	//If the size is less than 1, list is sorted
	if(right - left < 1)
		return;
	
	//Choosing left-most element as pivot
	//pivot = a[left];
	//parting the list according to the pivot
	partition = part(a, left, right);
	//Recursive call to sort individual parts
	quickSort(a, left, partition - 1);
	quickSort(a, partition + 1, right);
}

//Function to divide the given array into 2 according to the pivot element
//Takes a pointer to the array, and left and right pointers as input
//Returns position of the pivot element
int part(int *a, int left, int right)
{
	int l = left + 1, r = right, tmp;	//Marking l as next to the first(pivot) element, and r as the last element
	
	//Infinite loop to move the smaller than pivot elements to left, and rest to right
	while(1)
	{
		while(a[l] <= a[left])				//Change the sign for descending order
			l++;
		while(a[r] > a[left])				//Change the sign for descending order
			r--;
		//If left and right pointer cross, full array has been traversed
		if(l >= r)
			break;
		else //Exchanging left and right elements if not appropriate
		{
			tmp = a[l];
			a[l] = a[r];
			a[r] = tmp;
		}
	}
	
	//Swapping left-most (pivot) element with the last smaller than pivot element
	tmp = a[left];
	a[left] = a[r];
	a[r] = tmp;
	
	return r;
}

