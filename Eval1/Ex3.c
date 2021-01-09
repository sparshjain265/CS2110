/*
Program Name	: Ex3.c 
Description		: Exercise 1 - Q3
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
	//Declaring required variables
	struct node *head, *ptr, *p, *reverse, *pt;
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
	ptr->next = NULL;
	
	//Assigning Data and creating subsequent nodes
	for(i = 0; i < N; i++)
	{	
		printf("Enter Data: ");
		scanf(" %d", &head->data);
		//Allocating new memory if it is not the last required node
		if(i != N-1)
			p = (struct node*)malloc(sizeof(struct node));
		else	//else breaking out of the loop
			break;

		if(p == NULL)
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
		
		p->next = head;
		head = p;
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
				ptr->next = p->next;
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
	do
	{
		i = j = 0;
		//Asking for the node to delete
		printf("\n Enter the data you want to delete: ");
		scanf(" %d", &val);
		p = head;
		//if the first data is required to be deleted, updating the 'head' pointer
		while(p->data == val)
		{
			head = p->next;
			free(p);
			j++;
			p = head;
		}
		ptr = p;
		p = p->next;
		while(p != NULL)
		{
			//Else simply deleting the node 
			if(p->data == val)
			{
				ptr->next = p->next;
				free(p);
				j++;
				p = ptr->next;
				continue;
			}
			p = p->next;
			ptr = ptr->next;
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
	
	//Assigning the last node to 'reverse' list
	pt = ptr = head;
	i = 0;
	if(head->next != NULL)
		ptr = ptr->next;
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
		pt = pt->next;
	}
	p = reverse = ptr;
	reverse->next = NULL;
	pt->next = NULL;
	
	//Looping to remove last node from 'head' list and adding to 'reverse' list
	while(head != NULL)
	{
		pt = ptr = head;
		if(head->next != NULL)
			ptr = ptr->next;
		else i++; //counter to know when only 1 node is remaining
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
			pt = pt->next;
		}
		p->next = ptr;
		p = p->next;
		p->next = NULL;
		pt->next = NULL;
		if(i == 2) //counter will become 2 once the list is reversed
			head = NULL;
	}
	//assigning head to the reversed list
	head = reverse;
	
	//Printing the reversed list
	printf("\n\n Reversed List:");
	ptr = head;
	i = 1;
	while(ptr != NULL)
	{
		printf("\n Data #%d: %d", i, ptr->data);
		ptr = ptr->next;
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




