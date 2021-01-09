/*
Program Name	: binarySearch.c
Description		: Exercise 3a - Q2	: Binary Searching for a float in a sorted array
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: September 8, 2017
*/

#include<stdio.h>

int main()
{
	float list[100];					//Maximum length of the list is given as 100 in the problem statement
	int i, found = 0, n, a, b, m;	//Variable to store the counters, flags, and length of the input list
	float f, E = 0.49*10E-6;		//Variable to store the target value, and error
	
	while(1)								//Infinite loop, breaks when the user enters the of unique numbers in ascending order
	{	
		//Asking user for the length of list
		printf("\n Enter the length of the input list: ");
		scanf(" %d", &n);	
		
		//Mentioning the requirement to the user
		printf("\n Please enter a sorted list (Ascending Order) of unique numbers.");
		
		//Taking input of the list
		for(i = 0; i < n; i++)
		{
			printf("\n Enter data #%d: ", i+1);
			scanf(" %f", &list[i]);
		}
		
		//Checking whether the list satisfies the requirements
		for(i = 1; i < n; i++)
		{
			if(list[i-1] >= list[i])
			{
				printf("\n The given list is not according to the specification! Try Again!!!");
				i = n + 1;	//If not, set i to n+1 which is otherwise unachievable and break
				break;
			}
		}
		
		//If i is not n + 1, requirements are met and the loop can break; else retake the input
		if(i != n+1)
			break;			
	}
	
	//Ask the user for target value
	printf("\n Enter the value you want to search for: ");
	scanf(" %f", &f);
	
	//Setting the premise for binary search: a being lower bound, b being upper bound, and m being the middle value
	a = 0;
	b = n-1;
	m = (b+a)/2;
	//Infinite while loop to implement Binary Search
	//Breaks only if a match is found or it is confirmed that targer is not present
	while(1)
	{
		//If the targer lies within the error range, flags found as 1 and breaks the loop
		if(list[m] >= (f-E) && list[m] <= (f+E))
		{
			found = 1;
			break;
		}
		//If lower and upper bound are the same, target is not present in the list, flag is already set to 0, breaks the loop
		else if(b == a)
			break;
		//If the target is less than the mid value, search in the first half of the list
		else if(list[m] > (f-E))
		{
			b = m - 1;
			m = (b+a)/2;
		}
		//If the target is more than the mid value, search in the second half of the list
		else if(list[m] < (f+E))
		{
			a = m + 1;
			m = (b+a)/2;
		}
	}
	
	//Print Yes if found, No otherwise
	if(found == 1)
		printf("\n Yes");
	else
		printf("\n No");
	
	printf("\n\n");
	return 0;
}







































