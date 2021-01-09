/*
Program Name	: Ex5.c 
Description		: Exercise 1 - Q5
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: August 15, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Creating Structure node with self referencial pointers for doubly linked list
struct node
{
	int data;
	struct node *next;
	struct node *prev;
};

int main()
{
	//Declaring required variables
	struct node *head, *tail, *ptr, *p, *reverse, *pt;
	int i, N, j, val;
	
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
	tail = ptr;
	ptr->prev = NULL;
	ptr->next = NULL;
	p = ptr;
	
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
			ptr->next = NULL;
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
		ptr->prev = p;
		ptr->next = NULL;
		tail = ptr;
		p = p->next;
	}
	
	//Printing All Data in the list
	printf("\n Your List: ");
	ptr = head;
	i = 1;
	while(ptr != NULL)
	{
		printf("\n Data #%d: %d", i, ptr->data);
		ptr = ptr->next;
		i++;
	}
	
	
	do
	{
		i = j = 0;
		//Asking where to add the new node
		printf("\n Enter the data you want to add the new node after: ");
		scanf(" %d", &val);
		p = head;
		while(p != NULL)
		{
			if(p->data == val)
			{
				//Creating new node
				ptr = (struct node*)malloc(sizeof(struct node));
				//Checking if memory is allocated
				if(ptr == NULL)
				{	
					printf("Sorry, Not Enough Memory to add a new node!");
					break;
				}
				if(p->next == NULL) //Updating tail if the element is the last
					tail = ptr;
				ptr->next = p->next;
				ptr->prev = p;
				p->next->prev = ptr;
				p->next = ptr;
				//Entering Data in new node
				printf("\n Enter new Data: ");
				scanf(" %d", &ptr->data);
				j = 1;
				break;
			}
			p = p->next;
		}
		if(j == 0) //If the given data is not found, asking again
		{
			printf("\n Error: Data Not Found!");
			printf("\n Enter 1 to try again, 0 to continue... ");
			scanf(" %d", &i);
		}
	}while(i == 1); //Repeating until a new node is entered or the user does not want to add a new node
	
	//Printing the updated list
	printf("\n Updated List:");
	ptr = head;
	i = 1;
	while(ptr != NULL)
	{
		printf("\n Data #%d: %d", i, ptr->data);
		ptr = ptr->next;
		i++;
	}
	j = 0;
	do
	{
		i = 0;
		//Asking for the node to delete
		printf("\n Enter the data you want to delete: ");
		scanf(" %d", &val);
		p = head;
		
		while(p != NULL)
		{
			 
			if(p->data == val)
			{
				if((p->prev == NULL) && (p->next == NULL))
				{
					head = tail = NULL;
					free(p);
					j++;
				}
				else if(p->prev == NULL)
				{
					head = p->next;
					p = p->next;
					free(p->prev);
					p->prev = NULL;
					j++;
				}
				else if(p->next == NULL)
				{
					tail = p->prev;
					p->prev->next = NULL;
					free(p);
					break;
					j++;
				}
				else
				{	
					p->prev->next = p->next;
					p->next->prev = p->prev;
					ptr = p;
					p = p->next;
					free(ptr);
					j++;
				}
			}
			else p = p->next;			
		}
		if(j == 0) //If the node is not found, asking again
		{
			printf("\n Error: Data Not Found!");
			printf("\n Enter 1 to try again, 0 to continue... ");
			scanf(" %d", &i);
		}
	}while(i == 1); //Repeated until a node is deleted or the user does not want to delete a node
	
	//Printing the updated list
	printf("\n Updated List:");
	ptr = head;
	i = 1;
	while(ptr != NULL)
	{
		printf("\n Data #%d: %d", i, ptr->data);
		ptr = ptr->next;
		i++;
	}
	
	
	//Printing the reversed list
	printf("\n\n Reversed List:");
	ptr = tail;
	i = 1;
	while(ptr != NULL)
	{
		printf("\n Data #%d: %d", i, ptr->data);
		ptr = ptr->prev;
		i++;
	}
	
	//Freeing the allocated memory to prevent memory leak
	while(head != NULL)
	{
		ptr = head;
		head = head->next;
		free(ptr);
	}
	
	printf("\n\n");
	
	return 0;
}




