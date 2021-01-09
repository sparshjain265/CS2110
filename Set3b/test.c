/*
Program Name:	mergeSort.c
Description	: 	Set 3b: Ex1 - implementing merge sort using recursive call in ascending order
Programmer	:	Sparsh Jain
Roll No		: 	111601026
Date			: 	September 12, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

//Function Declarations
char ** mergeSort(char **a, int n);				//Function to merge-sort a given integer array in ascending order
char ** merge(char **x, char **y, int a, int b);//Function to merge 2 sorted integer arrays into 1 sorted integer array (ascending order)

int main()
{
	int n, i, left, right;
	char **a;
	printf("\n Enter n: ");
	scanf(" %d", &n);	
	a = (char **)calloc(n, sizeof(char *));		//Allocating only required amount of memory as array
	for(i = 0; i < n; i++)
		a[i] = (char *)calloc(31, sizeof(char));
	
	//Taking input from the user
	for(i = 0; i < n; i++)
	{
		printf("\n Enter data #%d (max 30 characters with only alphabets): ", i+1);
		scanf(" %s", a[i]);
	}
	
	//Calling function mergeSort to sort the given integer array
	a = mergeSort(a, n);
	
	//Printing the sorted list
	printf("\n Sorted List: ");
	for(i = 0; i < n; i++)
		printf("\n %s", a[i]);
	
	//Freeing the dynamically allocated memory to prevent memory leak
	free(a);
	
	printf("\n\n");
	return 0;
}

//Function to merge-sort a given integer array in ascending order
//Takes pointer to the array and length of array as arguements
//Returns sorted array
char ** mergeSort(char **a, int n)
{
	int i;
	char **x, **y;
	
	//If length of the array is 1, it is already sorted
	if(n == 1)	return a;
	
	//Allocating only required amount of memory as array
	x = (char **)calloc(n/2, sizeof(char *));
	//for(i = 0; i < n/2; i++)
		//x[i] = (char *)calloc(25, sizeof(char));
	y = (char **)calloc(n - n/2, sizeof(char *));
	//for(i = 0; i < n - n/2; i++)
		//y[i] = (char *)calloc(25, sizeof(char));
	
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
char ** merge(char **x, char **y, int a, int b)
{
	int i = 0, j = 0, k;
	char **c;
	c = (char **)calloc(a + b, sizeof(char *));	//Allocating only required amount of memory as array
	
	while(i < a && j < b)						//If there are elements in both the arrays, adding the smaller to the new array
	{
	/*
		if(x[i] < y[j])
			c[i+j] = x[i++];
		else 
			c[i+j] = y[j++];
	*/
	//Checking for all characters: loop breaks when the priority is found or the last character is checked
		for(k = 0; k < 31; k++)
		{
			if(x[i][k] == '\0')					//Shorter word first
			{
				c[i+j] = x[i++];
				break;
			}
			if(y[j][k] == '\0')					//Shorter word first
			{
				c[i+j] = y[j++];
				break;
			}
			if(x[i][k] >= 'A' && x[i][k] <= 'Z' && y[j][k] >= 'A' && y[j][k] <= 'Z')	//If both words have capital letters: compare
			{
			if(x[i][k] < y[j][k])
			{
				c[i+j] = x[i++];
				break;
			}
			if(x[i][k] > y[j][k]);
			{
				c[i+j] = y[j++]; 
				break;
			}
			}
			if(x[i][k] >= 'a' && x[i][k] <= 'z' && y[j][k] >= 'a' && y[j][k] <= 'z')	//If both words have small letters: compare
			{
			if(x[i][k] < y[j][k])
			{
				c[i+j] = x[i++];
				break;
			}
			if(x[i][k] > y[j][k]);
			{
				c[i+j] = y[j++]; 
				break;
			}
			}
			if(x[i][k] >= 'A' && x[i][k] <= 'Z' && y[j][k] >= 'a' && y[j][k] <= 'z')	//If one has capital and one has small: compare absolute, if same capital gains priority
			{
			if(tolower(x[i][k]) < y[j][k])
			{
				c[i+j] = x[i++];
				break;
			}
			if(tolower(x[i][k]) > y[j][k])
			{
				c[i+j] = y[j++]; 
				break;
			}
			if(tolower(x[i][k]) == y[j][k])
			{
				c[i+j] = x[i++];
				break;
			}
			}
			if(x[i][k] >= 'a' && x[i][k] <= 'z' && y[j][k] >= 'A' && y[j][k] <= 'Z')	//If one has capital and one has small: compare absolute, if same capital gains priority
			{
			if(x[i][k] < tolower(y[j][k]))
			{
				c[i+j] = x[i++];
				break;
			}
			if(x[i][k] > tolower(y[j][k]))
			{
				c[i+j] = y[j++]; 
				break;
			}
			if(x[i][k] == tolower(y[j][k]))
			{
				c[i+j] = y[j++];
				break;
			}
			}	
		}
	
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

