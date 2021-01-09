/*
Program Name	: Ex4.c 
Description		: Exercise 1 - Q4
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: August 8, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Creating Structure node with self referencial pointer
struct node
{
	int data;
	struct node *next;
};

int main()
{
	//Declaring necessary variables
	struct node *head, *ptr;
	int i = 0,j, ch = 0, val, N;
	
	//Asking user for 'N'
	printf("\n Enter the number of data entries: ");
	scanf(" %d", &N);
	
	//Creating first node
	ptr = (struct node*)malloc(sizeof(struct node));
	if(ptr == NULL)
	{
		//Program will terminate if unable to provide enough memory
		printf("Not Enough Memory! \nTerminating Program!");
		return 0;
	}
	head = ptr;
	ptr->next = head; //Creating Circular Linked List
	
	//Assigning Data and creating subsequent nodes
	for(i = 0; i < N; i++)
	{	
		printf("Enter Data #%d: ", i+1);
		scanf(" %d", &ptr->data);
		//Allocating new memory if it is not the last required node
		if(i != N-1)
			ptr->next = (struct node*)malloc(sizeof(struct node));
		else	//else breaking out of the loop
		{
			ptr->next = head; //maintaining the circular linked list
			break;
		}
		if(ptr->next == NULL)
		{
			//Program will terminate if unable to provide enough memory
			printf("Not Enough Memory! \nTerminating Program!");
			//Preventing memory leak before terminating program
			for(j = 0; j < i; j++)
			{
				ptr = head;
				head = head->next;
				free(ptr);
			}
			return 0;
		}
		ptr = ptr->next;
	}
	
	do
	{
		j = 0; 
		//Asking the value to be searched
		printf("Enter the data you want to search: ");
		scanf(" %d", &val);
		//Searching the data
		ptr = head;
		for(i = 0; i < N; i++)
		{
			if(ptr->data == val)
			{	
				//Notify if found
				printf("\n %d found at #%d", val, i+1);
				i = -1;
				break;
			}
			ptr = ptr->next;		
		}
		if(i != -1) //Notify if not found
			printf("\n %d not found!", val);
		//Asking if the user wants to search another data
		printf("\nEnter 1 to search another data...");
		scanf(" %d", &j);
	}while(j == 1);	
	
	//Freeing allocated memory to prevent memory leak
	for(i = 0; i < N; i++)
	{
		ptr = head;
		head = head->next;
		free(ptr);
	}
	
	printf("\n\n");
	return 0;
}
