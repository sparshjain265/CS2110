/*
Program Name	: Ex1.c 
Description		: Exercise 2b - Q1
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: August 29, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//struct node for a stack
struct stack
{
	char data[50];
	struct stack *next;
};

//typedef for our convinience
typedef struct stack stack;

stack * newStack();								//Function to create a new stack, returns pointer to the new stack
void stackPush(stack **stk, char x[50]);	//Function to push an element in the stack, takes a pointer to stack and the data as input
char * stackPop(stack **stk);					//Function to pop an element from the stack, takes a pointer to stack as input, returns data or error message as output
int stackIsEmpty(stack *stk);					//Function to check whether the stack is empty, takes a stack pointer, returns 0 if stack is empty
void stackTop(stack *stk);						//Function to print the topmost element of the stack, takes a stack pointer as input
void printMenu();									//Function to print the menu of the program

int main()
{	
	//Declaring required variables
	int choice, length = -1;
	char data[50], *d;
	//Creating new stack called myStack
	stack *myStack = newStack();
	printMenu();
	//Infinite loop until the user asks to end the program
	while(1)
	{	
		//Asking the user for choice
		printf("\nEnter your choice: ");
		scanf(" %d", &choice);
		//Implimenting choice using switch
		switch(choice)
		{
			case 1:	printf("\nEnter the movie name: ");
						scanf(" %49[^\n]s", data);
						stackPush(&myStack, data);
						length++;
						break;
			case 2: 	d = stackPop(&myStack);
						printf("\n %s", d);
						if(strcmp(d, "Stack Empty!"))
							length--;
						break;
			case 3: 	stackTop(myStack);
						break;
			case 4: 	printf("Length = %d", length + 1);
						break;
			case 5: 	while(stackIsEmpty(myStack))
						{
							stackTop(myStack);
							d = stackPop(&myStack);
							length--;
						}
						break;
			case 6:	printf("\n\n");
						while(stackIsEmpty(myStack))
						{
							d = stackPop(&myStack);
							length--;
						}
						return 0;
			default: printf("\nUnknown response! Try again!");
						printMenu();
		}
	}
}

//Function definition to create a new stack
stack * newStack()
{
	stack *stk = NULL;
	return stk;	
}

//Function Definition to push into stack
void stackPush(stack **stk, char x[50])
{
	stack *ptr;
	ptr = (stack *)malloc(sizeof(struct stack));
	strcpy(ptr->data, x);
	ptr->next = *stk;
	*stk = ptr;
}

//Function definition to pop from a stack
char * stackPop(stack **stk)
{
	stack *ptr;
	static char x[50];
	if(stackIsEmpty(*stk))
	{
		strcpy(x, (*stk)->data);
		ptr = *stk;
		(*stk) = (*stk)->next;
		free(ptr);
		return x;
	}
	strcpy(x, "Stack Empty!");
	return x;
}

//Function Definition to check the stack
int stackIsEmpty(stack *stk)
{
	if(stk == NULL)
		return 0;
	return 1;
}

//Function Definition to read the stack
void stackTop(stack *stk)
{	
	if(stackIsEmpty(stk))
		printf("\n %s", stk->data);
	else
		printf("\n Stack Empty!");
}

//Function Definition to print the Menu
void printMenu()
{
		printf("\nMenu");
		printf("\n====");
		printf("\n 1. Push");
		printf("\n 2. Pop");
		printf("\n 3. Read the Top");
		printf("\n 4. Check the length of the stack");
		printf("\n 5. Print the stack (Caution: This will delete your stack)");
		printf("\n 6. Exit the program");
}
