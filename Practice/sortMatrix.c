/*
Program Name: sortMatrix.c
Description	: sort a given matrix in O(n^2 logn) : the given matrix is sorted in ascending order along rows and columns
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: September 19, 2017
*/

#include<stdio.h>
#include<stdlib.h>

int input(int **A, int n);
void sortList(int **A, int *list, int n);

int main()
{
	int **A, *list, n, i;
	
	while(1)
	{
		printf("\n Enter the number of rows in the matrix: ");
		scanf(" %d", n);
	
		A = (int **)calloc(n, sizeof(int *));
		for(i = 0; i < n; i++)
			A[i] = (int *)calloc(n, sizeof(int));
	
		i = input(A, n);
	
		if(i == 0)
			break;
	
		for(i = 0; i < n; i++)
			free(A[i]);
		free(A);
	}
	
	list = (int *)calloc(n*n, sizeof(int *));
	
	sortList(A, list, n);
	
	printf("\n\n");
	for(i = 0; i < n; i++)
		free(A[i]);
	free(A);
	free(list);
	return 0;
}

void sortList(int **A, int *list, int n)
{
	int i = 0, j = 0;	
}

int input(int **A, int n)
{
	int i, j;
	
	printf("\n Please enter the data of matrix in ascending order along rows and columns
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("\n Enter element in [%d][%d]: ", i, j);
			scanf(" %d", &A[i][j]);
			if(j > 0 && A[i][j] < A[i][j-1])
			{
				printf("\n Data not ascending! Try again.");
				return -1;
			}
			if(i > 0 && A[i][j] < A[i-1][j])
			{
				printf("\n Data not ascending! Try again.");
				return -1;
			}
		}
	}
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf(" \t %d ", A[i][j]);
		printf("\n");
	}
	return 0;
}
