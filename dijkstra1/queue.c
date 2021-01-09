/*
File Name	: queue.c
Description	: Function definitions to implement a queue using linked lists
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: October 17, 2017
*/

#include<stdlib.h>
#include "queue.h"

//Function Definition for enqueue
//Takes a pointer to queue and integer data as input
void enqueue(struct queue *q, int data)
{
	//Initializing new node ptr
	struct node *ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->next = NULL;
	
	//Updating queue front if queue is empty, else updating next of previous rear
	if(isempty(*q) == 1)
		q->front = ptr;
	else 
		q->rear->next = ptr;
	
	//Updating rear
	q->rear = ptr;	
}

//Function Definition for dequeue
//Takes a pointer to queue
//Returns integer data
int dequeue(struct queue *q)
{
	struct node *ptr = q->front;	//Storing front in ptr
	int data = q->front->data;		//Storing data
	q->front = q->front->next;		//Updating front
	free(ptr);							//Deleting the node
	return data;						//Returning the data
}

//Function Definition to check if a queue is empty
//Takes pointer to queue
//Returns 1 if queue is empty, 0 otherwise
int isempty(struct queue q)
{
	//If front is NULL, queue is empty
	if(q.front == NULL)
		return 1;
	else return 0;
}
