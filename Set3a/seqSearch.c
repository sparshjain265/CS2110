/*
Program Name	: seqSearch.c
Description		: Exercise 3a - Q1	: Sequential Searching for a float in a sorted array
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: September 8, 2017
*/

#include<stdio.h>

int main()
{
	float list[100];				//Maximum length of the list is given as 100 in the problem statement
	int i, n;						//Variable to store the counter, and length of the input list
	float f, E = 0.49*10E-6;	//Variable to store the target value, and error
	
	while(1)							//Infinite loop, breaks when the user enters the of unique numbers in ascending order
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
	
	//For loop to traverse through the list
	for(i = 0; i < n; i++)
	{	
		//If the list element lies in the error range, print yes and exit
		if(list[i] >= (f - E) && list[i] =< (f + E))
		{
			printf("\n Yes");
			printf("\n\n");
			return 0;
		}
		//If the list element is greater than the target value, target is no longer in the list due to ascending order
		else if(list[i] > (f + E))
			break;			
	}
	//If the program reaches here, member was not in the list, print no and exit
	printf("\n No");
	
	printf("\n\n");
	return 0;
}
