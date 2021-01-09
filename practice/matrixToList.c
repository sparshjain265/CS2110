/*
Program Name: matrixToList.c 
Description : program to convert a sorted (row and column wise) matrix in a sorted list
Programmer  : Sparsh Jain
Roll No     : 111601026
Date        : September 25, 2017
*/

#include<stdio.h>
#include<stdlib.h> 

struct node
{
   int data;
   int next;
};

struct node * merge(int **A, int n);

int main()
{
   int **A, n, i, j;
   struct node *list;

   printf("\nEnter n: ");
   scanf(" %d", &n);

   A = (int **)calloc(n, sizeof(int *));
   for(i = 0; i < n; i++)
      A[i] = (int *)calloc(n, sizeof(int));
   

   //Assuming correct input
   for(i = 0; i < n; i++)
      for(j = 0; j < n; j++)
      {
         printf("\n Enter A[i][j]: ");
         scanf(" %d", &A[i][j]);
      }
   
   list = merge(int **A, int n);

   printf("\n\n");
   return 0;
}

struct node * merge(int **A, int n)
{
   struct node * list;
   int i, j;

   for(i = 0; i < n; i++)
      for(j = 0; j < n; j++)
         addNode

   return list;
}

