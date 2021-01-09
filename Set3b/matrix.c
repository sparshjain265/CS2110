/*
Program Name:	matrix.c
Description	: 	Finding an element in a sorted matrix with time complexity = O(r+c) or O(n) in general, space complexity = O(1)
Programmer	:	Sparsh Jain
Roll No		: 	111601026
Date			: 	September 18, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Function Declarations
int input(int **A, int row, int col);														//Function to take sorted input in a matrix	
void search(int **A, int row, int col, int *r, int *c, int find, int order);	//Function to search an element in a sorted matrix

int main()
{
	int **A, row, col, i, order = -1, r = -1, c = -1, find;							//Declaring required variables
	
	//Infinite Loop until user enters values of a sorted matrix
	//Order can be Ascending or Descending but same for both rows and columns
	while(1)
	{
		//Asking the user for number of rows and columns
		printf("\n Enter the number of rows: ");
		scanf(" %d", &row);
		printf("\n Enter the number of columns: ");
		scanf(" %d", &col);
		
		//Allocating dynamic memory to A as matrix
		A = (int **)calloc(row, sizeof(int *));
		for(i = 0; i < row; i++)
			A[i] = (int *)calloc(col, sizeof(int));
		
		//Calling input function to input the values of the matrix
		order = input(A, row, col);	//order = 1 -> Ascending, order = 2 -> Descending
		if(order != -1)					//Order will be -1 if input was incorrect, hence break for correct input
			break;	

		//Program will reach here only if the input was incorrect
		//Freeing the useless memory to prevent memory leak
		for(i = 0; i < row; i++)
			free(A[i]);
		free(A);
	}

	//Asking the user for the element to search for
	printf("\n Enter the element you want to search: ");
	scanf(" %d", &find);

	//Calling the function search to find the element given by the user
	search(A, row, col, &r, &c, find, order);
	// if element is found, print it's position
	if(r != -1)
		printf("\n %d found at [%d][%d].", find, r, c);
	else	//else print the message
		printf("\n %d not found.", find);
	
	//Free the memory before terminating the program to prevent memory leak
	for(i = 0; i < row; i++)
		free(A[i]);
	free(A);

	printf("\n\n");
	return 0;
}

//Defining function search to search an element in a sorted matrix
//Matrix can be either Ascending or Descending but the order should be same for both rows and columns
//Takes pointer to the matrix, number of rows, number of columns, a pointer to row index, a pointer to column index, element to find, and the order of the sort as inputs
//Gives no output, but changes the values of of row index and column index to the position of the found element, leaves them unchanged if not found
void search(int **A, int row, int col, int *r, int *c, int find, int order)
{
	int found = 0, i = 0, j = col-1;
	while(i < row && j >= 0)	//Starting from the top right corner of the matrix
	{
		if(order == 1)				//If Ascending
		{
			if(A[i][j] == find)	//change the index and return if found
			{
				*r = i;
				*c = j;
				return;
			}
			if(A[i][j] > find)	//Move Left if the element is greater than required
				j--;
			else i++;				//Move Down if the element is smaller than required
		}
		else							//If Descending
		{
			if(A[i][j] == find)	//change the index and return if found
			{
				*r = i;
				*c = j;
				return;
			}
			if(A[i][j] < find)	//Move Left if the element is smaller than required
				j--;
			else i++;				//Move Down if the element is greater than required
		}
	}
}

//Defining Function input to take sorted input in a matrix
//Matrix can be either Ascending or Descending but the order should be same for both rows and columns
//Takes pointer to the matrix, number of rows, and number of columns as input
//Returns the order of the matrix: 1 if Ascending, 2 if Descending
int input(int **A, int row, int col)
{
	int r, c, order = 0, count = 0;	//Initial value of order is set to 0
	
	//Printing the requirements
	printf("\n Please Enter a sorted (Either Ascending or Descending) matrix along both rows and columns!");
	printf("\n Order should be same along the rows and columns!\n");
	
	//Looping to cover the entire matrix
	for(r = 0; r < row; r++)
	{
		count = 0;												//reset count for every loop
		for(c = 0; c < col; c++)
		{
			printf("Enter Data[%d][%d]: ", r, c);	//Asking for data entry
			scanf(" %d", &A[r][c]);
			while(order == 0 && count < c)				//If order hasn't been set, and count is less than the number of elements in the row, set the order
			{
				if(A[r][c] < A[0][0])
					order = 2;	//Descending
				else if(A[r][c] > A[0][0])
					order = 1;	//Ascending
				count++;
			}
			if(order == 1)										//If order is set as ascending, check for irregularities
			{
				if(c > 0 && A[r][c] < A[r][c-1])			//Irregularity check in column
				{
					printf("\n Wrong input! Enter Sorted Matrix!");
					return -1;
				}
				if(r > 0 && A[r][c] < A[r-1][c])			//Irregularity check in row
				{
					printf("\n Wrong input! Enter Sorted Matrix!");
					return -1;
				}
			}
			if(order == 2)										//If order is set as descending, check for irregularities
			{
				if(c > 0 && A[r][c] > A[r][c-1])			//Irregularity check in column
				{
					printf("\n Wrong input! Enter Sorted Matrix!");
					return -1;
				}
				if(r > 0 && A[r][c] > A[r-1][c])			//Irregularity check in row
				{
					printf("\n Wrong input! Enter Sorted Matrix!");
					return -1;
				}
			}
		}
	}
	
	//Print the matrix in conventional form once all inputs are taken
	for(r = 0; r < row; r++)
	{
		for(c = 0; c < col; c++)
			printf(" \t%d", A[r][c]);
		printf("\n");
	}

	//Return order
	return order;
}
