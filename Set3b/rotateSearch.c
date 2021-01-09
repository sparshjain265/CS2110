/*
Program Name	: rotateSearch.c
Description		: Searching in a sorted (Ascending) array rotated any number of times using O(log n) algorithm
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: September 18, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Function Declarations
void input(int *A, int n);                      //Function to input data in an array
int findRotate(int *A, int a, int b, int find); //Function to search an element in a rotated-sorted array(Ascending Order)

int main()
{
   int *A, n, find, index;

   //Asking the user for the number of data entries, allocating memory and taking input from the user
   printf("\n Enter the number of data in the list: ");
   scanf(" %d", &n);
   A = (int *)calloc(n, sizeof(int));
   input(A, n);

   //Asking for the element to find and then calling function findRotate to assign index of the required element
   printf("\n Enter the element you want to find: ");
   scanf(" %d", &find);
   index = findRotate(A, 0, n-1, find);

   //If index is -1, element not found. Else print the index
   if(index == -1)
      printf("\n %d not found.", find);
   else
      printf("\n %d found at index %d.", find, index);

   printf("\n\n");
   free(A); //Free memory before terminating the program
   return 0;
}

//Defining function to search an element in a rotated-sorted array (Ascending order)
//Takes pointer to the array, least index, greatest index, and element to be searched as inputs
//Returns the index of the element (It may return any index in case of repeating results depending on its position in the array). (-1 if not found)
int findRotate(int *A, int a, int b, int find)
{
   int m = (a + b)/2, tmp; //Set m as middle of a and b
   if(a > b)               //If least index > greatest index, array is traversed: return -1
      return -1;
   if(A[m] == find)        //If element is middle term, return middle index
      return m;
   //If first half is strictly increasing
   //If element to be found lies in between the least and middle index, return the search result from first half
   //Else return the search result from the second half
   if(A[a] < A[m])
   {
      if(find >= A[a] && find <= A[m])          //change for descending order
         return findRotate(A, a, m-1, find);
      else return findRotate(A, m+1, b, find);
   }
   //If first and middle element are same
   //Check in the first half, if found, return the index
   //Else check in the second half
   else if(A[a] == A[m])
   {
      tmp = findRotate(A, a, m-1, find);
      if(tmp != -1)
         return tmp;
      else
         return findRotate(A, m+1, b, find);
   }
   //If second half is strictly increasing
   //If element to be found lies between the middle and greatest index, return the search result from second half
   //Else return the search result from the first half
   else if(A[m] < A[b])
   {
      if(find >= A[m] && find <= A[b])          //change for descending order
         return findRotate(A, m+1, b, find);
      else return findRotate(A, a, m-1, find);
   }
   //If middle and last element are same
   //Check in the second half, if found, return the index
   //Else check in the first half
   else if(A[m] == A[b])
   {
      tmp = findRotate(A, m+1, b, find);
      if(tmp != -1)
         return tmp;
      else
         return findRotate(A, a, m-1, find);
   }
}

//Defining function input to take data from the user and input it in an Array
//Takes pointer to an array and it's size as inputs
void input(int *A, int n)
{
   int i;
   for(i = 0; i < n; i++)        //Loop to traverse through the array
   {
      printf("\n Enter Data: "); //Prompting for data
      scanf(" %d", &A[i]);       //Scanning data
   }
}