/*
Program Name: zero.c 
Description : program to set row and column to zero if a cell is zero
Programmer  : Sparsh Jain
Roll No     : 111601026
Date        : September 25, 2017
*/

#include<stdio.h> 
#include<stdlib.h> 

int main()
{
   int **A, **B, row, col, i, j, k;

   printf("\n Enter the number of rows: ");
   scanf(" %d", &row);
   printf("\n Enter the number of columns: ");
   scanf(" %d", &col);

   A = (int **)calloc(row, sizeof(int *));
   B = (int **)calloc(row, sizeof(int *));
   for(i = 0; i < row; i++)
   {
      A[i] = (int *)calloc(col, sizeof(int));
      B[i] = (int *)calloc(col, sizeof(int));
   }
   
   for(i = 0; i < row; i++)
      for(j = 0; j < col; j++)
      {
         printf("\n Enter A[%d][%d]", i, j);
         scanf(" %d", &A[i][j]);
         B[i][j] = A[i][j];
      }
   
      printf("\n Your Matrix:\n");
      for(i = 0; i < row; i++)
      {
         for(j = 0; j < col; j++)
            printf("\t %d", A[i][j]);
         printf("\n");
      }

   for(i = 0; i < row; i++)
      for(j = 0; j < col; j++)
      {
         if(A[i][j] == 0)
         {
            for(k = 0; k < row; k++)
               B[k][j] = 0;
            for(k = 0; k < col; k++)
               B[i][k] = 0;
         }
      }
   
   printf("\n Your New Matrix:\n");
   for(i = 0; i < row; i++)
   {
      for(j = 0; j < col; j++)
         printf("\t %d", B[i][j]);
      printf("\n");
   }

   printf("\n\n");
   return 0;
}