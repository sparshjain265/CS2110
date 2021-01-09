/*
Program Name	: Ex6.c 
Description		: Exercise 1 - Q6
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: August 15, 2017
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
	struct node *head1, *ptr, *head2, *list, *p1, *p2;
	int i = 0,j, ch = 0, val, N1, N2;
	
	//Asking user for 'N'
	printf("\n Enter the number of data entries in first list: ");
	scanf(" %d", &N1);
	
	//Creating first node
	ptr = (struct node*)malloc(sizeof(struct node));
	if(ptr == NULL)
	{
		//Program will terminate if unable to provide enough memory
		printf("Not Enough Memory! \nTerminating Program!");
		return 0;
	}
	head1 = ptr;
	ptr->next = head1; //Creating Circular Linked List
	
	//Assigning Data and creating subsequent nodes
	for(i = 0; i < N1; i++)
	{	
		printf("Enter Data #%d: ", i+1);
		scanf(" %d", &ptr->data);
		//Allocating new memory if it is not the last required node
		if(i != N1-1)
			ptr->next = (struct node*)malloc(sizeof(struct node));
		else	//else breaking out of the loop
		{
			ptr->next = head1; //maintaining the circular linked list
			break;
		}
		if(ptr->next == NULL)
		{
			//Program will terminate if unable to provide enough memory
			printf("Not Enough Memory! \nTerminating Program!");
			//Preventing memory leak before terminating program
			for(j = 0; j < i; j++)
			{
				ptr = head1;
				head1 = head1->next;
				free(ptr);
			}
			return 0;
		}
		ptr = ptr->next;
	}
	
	N2 = N1 + 1;
	while(N2 >= N1)
	{
		//Asking user for 'N'
		printf("\n Enter the number of data entries in second list (less than %d): ", N1);
		scanf(" %d", &N2);
		
	}
	
	//Creating first node
	ptr = (struct node*)malloc(sizeof(struct node));
	if(ptr == NULL)
	{
		//Program will terminate if unable to provide enough memory
		printf("Not Enough Memory! \nTerminating Program!");
		return 0;
	}
	head2 = ptr;
	ptr->next = head2; //Creating Circular Linked List
	
	//Assigning Data and creating subsequent nodes
	for(i = 0; i < N2; i++)
	{	
		printf("Enter Data #%d: ", i+1);
		scanf(" %d", &ptr->data);
		//Allocating new memory if it is not the last required node
		if(i != N2-1)
			ptr->next = (struct node*)malloc(sizeof(struct node));
		else	//else breaking out of the loop
		{
			ptr->next = head2; //maintaining the circular linked list
			break;
		}
		if(ptr->next == NULL)
		{
			//Program will terminate if unable to provide enough memory
			printf("Not Enough Memory! \nTerminating Program!");
			//Preventing memory leak before terminating program
			for(j = 0; j < i; j++)
			{
				ptr = head2;
				head2 = head2->next;
				free(ptr);
			}
			return 0;
		}
		ptr = ptr->next;
	}
	
	//Creating first node
	ptr = (struct node*)malloc(sizeof(struct node));
	if(ptr == NULL)
	{
		//Program will terminate if unable to provide enough memory
		printf("Not Enough Memory! \nTerminating Program!");
		return 0;
	}
	list = ptr;
	ptr->next = list; //Creating Circular Linked List
	
	p1 = head1;
	p2 = head2;
	
	//Adding data to the merged list
	for(i = 0; i < (N1 + N2); i++)
	{
		if(i < (2*N2)) //Alternatively till the shorter list has elements
		{
			if((i % 2) == 0)	
			{
				ptr->data = p1->data;
				p1 = p1->next;
				ptr->next = (struct node*)malloc(sizeof(struct node));
				if(ptr->next == NULL)
				{
					printf("Not enough memory");
					break;
				}
				ptr = ptr->next;
				ptr->next = list;
			}
			else 
			{
				ptr->data = p2->data;
				p2 = p2->next;
				ptr->next = (struct node*)malloc(sizeof(struct node));
				if(ptr->next == NULL)
				{
					printf("Not enough memory");
					break;
				}
				ptr = ptr->next;
				ptr->next = list;
			}
		}
		else	//then assigning rest of the data at the end
		{
			ptr->data = p1->data;
			p1 = p1->next;
			ptr->next = (struct node*)malloc(sizeof(struct node));
			if(ptr->next == NULL)
			{
				printf("Not enough memory");
				break;
			}
			ptr = ptr->next;
			ptr->next = list;
		}
	}
	
	//Displaying merged list
	ptr = list;
	printf("\nMerged list:");
	for(i = 0; i < N1 + N2; i++)
	{
		printf("\nData #%d: %d", i+1, ptr->data);
		ptr = ptr->next;
	}
	
	//Freeing allocated memory to prevent memory leak
	for(i = 0; i < N1; i++)
	{
		ptr = head1;
		head1 = head1->next;
		free(ptr);
	}
	for(i = 0; i < N2; i++)
	{
		ptr = head2;
		head2 = head2->next;
		free(ptr);
	}
	for(i = 0; i < N1 + N2; i++)
	{
		ptr = list;
		list = list->next;
		free(ptr);
	}
	
	
	
	printf("\n\n");
	return 0;
}
