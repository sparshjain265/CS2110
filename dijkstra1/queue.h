/*
File Name	: queue.h
Description	: Function Declarations to implement a queue using linked lists
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: October 17, 2017
*/

//Structure node to implement queue with integer data 
struct node
{
	int data;
	struct node *next;
};

//Structure queue to implement queue
struct queue
{
	struct node *front;
	struct node *rear;
};

//Function Declarations for queue implementation
void enqueue(struct queue *q, int data);			
int dequeue(struct queue *q);
int isempty(struct queue q);
