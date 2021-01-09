/*
Program Name	: Ex2.c
Description		: Exercise 2b - Q2
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: September 5, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//Structure for a queue which contains max of 10 integers
typedef struct queue
{
    int data[10];
    int front;
    int rear;
} *queue;

queue newQueue();               //Function to create a new queue, returns pointer to the new queue
void enQueue(queue q, int x);   //Function to enQueue an element in a queue, takes the pointer to the queue and data as input
int deQueue(queue q);           //Function to deQueue an element from a queue, takes the pointer to the queue and returns the front element
int queueSize(queue q);         //Function to return the size of the queue, takes the pointer to queue as argument and returns the size
int queueIsEmpty(queue q);      //Function to check whether the queue is empty, takes the pointer to queue as argument, returns 0 if empty
void queueFront(queue q);       //Function to print the front element of the queue
void printMenu();               //Function to print the menu

int main()
{
    //Declaring choice and data variables
    int choice, data;
    //Creating new queue
    queue q = newQueue();
    //Printing menu
    printMenu();
    //Infinite Loop until the user chooses to end the program
    while(1)
    {
        //Asking the user for choice
        printf("\n Enter your choice: ");
        scanf("%d", &choice);
        //Implementing choice using switch
        switch(choice)
        {
            case 1: printf("\n Enter Data: ");
                    scanf("%d", &data);
                    enQueue(q,data);
                    break;
            case 2: if(queueIsEmpty(q))
            		  {
            		  		data = deQueue(q);
                    		printf("\n %d", data);
                    }
                    else printf("\n Queue Empty! Can't Dequeue!");
                    break;
            case 3: queueFront(q);
                    break;
            case 4: data = queueSize(q);
                    printf("\n Size: %d", data);
                    break;
            case 5: while(queueSize(q))
                    {
                        queueFront(q);
                        data = deQueue(q);
                    }
                    break;
            case 6: printf("\n\n");
                    free(q);
                    return 0;
            default:    printf("\nUnknown Response! Try Again!");
                        printMenu();
        }
    }
}

//Function definition to create a new queue
queue newQueue()
{
    queue q;
    q = (queue)malloc(sizeof(struct queue));
    q->front = 0;
    q->rear = -1;
    return q;
}

//Function definition to enQueue in the given queue
void enQueue(queue q, int x)
{
    //Print Error Message if Queue full
    if(queueSize(q) == 10)
        printf("\n Queue Full! Can't Enqueue!");
    else    //Else update rear, increment size and add data
    {
        if(q->rear == 9)
            q->rear = 0;
        else
            q->rear += 1;
        q->data[q->rear] = x;
    }
}

//Function definition to deQueue from the given queue
int deQueue(queue q)
{
	 int data;
        if(q->front == 9)
        {
            q->front = 0;
            data =  q->data[9];
            if(q->rear == 9)
            	q->rear = -1;
            return data;
        }

        else
        {
            q->front += 1;
            data =  q->data[q->front - 1];
            if(q->rear == q->front - 1)
            {
            	q->front = 0;
            	q->rear = -1;
            }
            return data;
        }
}

//Function definition to check the size
int queueSize(queue q)
{
	 //Return 0 if rear is -1 ie queue is empty
	 if(q->rear == -1)
	 	return 0;
    //Return the difference between rear and front for normal queue
    if(q->rear >= q-> front)
        return (q->rear - q->front + 1);
    else    //Add additional 10 if the queue has been cycled
        return (q->rear - q->front + 11);
}

//Function definition to check for an empty queue, returns 0 if queue is empty
int queueIsEmpty(queue q)
{
    return queueSize(q);
}

//Function definition to print the front element of the queue
void queueFront(queue q)
{
    if(queueIsEmpty(q)) //Print the front element if there is
        printf("\n Front: %d", q->data[q->front]);
    else                //Else print an error message
        printf("\n Queue Empty! Try to Enqueue first!");
}

//Function definition to print menu
void printMenu()
{
        printf("\nMenu");
		printf("\n====");
		printf("\n 1. Enqueue");
		printf("\n 2. Dequeue");
		printf("\n 3. Read the Front");
		printf("\n 4. Check the length of the queue");
		printf("\n 5. Print the queue (Caution: This will delete your queue)");
		printf("\n 6. Exit the program");
}
