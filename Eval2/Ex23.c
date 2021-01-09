/*
Program Name	: Ex3.c
Description		: Exercise 2b - Q1
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: September 5, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//struct node for a stack
struct stack
{
	int data;
	struct stack *next;
};

//typedef for our convinience
typedef struct stack stack;

stack * newStack();								//Function to create a new stack, returns pointer to the new stack
void stackPush(stack **stk, int x);	//Function to push an element in the stack, takes a pointer to stack and the data as input
int stackPop(stack **stk);					//Function to pop an element from the stack, takes a pointer to stack as input, returns data or error message as output
int stackIsEmpty(stack *stk);					//Function to check whether the stack is empty, takes a stack pointer, returns 0 if stack is empty
void stackTop(stack *stk);						//Function to print the topmost element of the stack, takes a stack pointer as input
//void printMenu();									//Function to print the menu of the program

int main()
{
	//Declaring required variables
	int i, a, b, length = -1;
	int data; char d[50];
	//Creating new stack called myStack
	stack *myStack = newStack();
    //Asking user for the postfix format & scanning it as a string
    printf("\n Enter Postfix: ");
    scanf(" %49[^\n]s", d);
    //Loop continues until all the characters are accounted for
    for(i = 0; i < strlen(d); i++)
    {
        //Calculations are done according to the rules
        if(d[i] > 47 && d[i] < 58)
        {
            stackPush(&myStack, (int)(d[i]-48));
            length++;
        }
        else if(d[i] == '+')
        {
            b = stackPop(&myStack);
            a = stackPop(&myStack);
            stackPush(&myStack, a+b);
            length--;
        }
        else if(d[i] == '-')
        {
            b = stackPop(&myStack);
            a = stackPop(&myStack);
            stackPush(&myStack, a-b);
            length--;
        }
        else if(d[i] == '*')
        {
            b = stackPop(&myStack);
            a = stackPop(&myStack);
            stackPush(&myStack, a*b);
            length--;
        }
        else if(d[i] == '/')
        {
            b = stackPop(&myStack);
            a = stackPop(&myStack);
            if(b == 0)  break;
            stackPush(&myStack, a/b);
            length--;
        }
    }

    //Only answer should remain in the stack. If there are more or less elements, the given expression was invalid
    if(length == 0)
    {
        printf("\n %s = %d", d, stackPop(&myStack));
        length--;
    }
    else printf("Invalid Expression");

    //Freeing any left over memory to prevent leakage
	while(stackIsEmpty(myStack))
    {
		data = stackPop(&myStack);
		length--;
	}
	return 0;
}

//Function definition to create a new stack
stack * newStack()
{
	stack *stk = NULL;
	return stk;
}

//Function Definition to push into stack
void stackPush(stack **stk, int x)
{
	stack *ptr;
	ptr = (stack *)malloc(sizeof(struct stack));
	ptr->data =  x;
	ptr->next = *stk;
	*stk = ptr;
}

//Function definition to pop from a stack
int stackPop(stack **stk)
{
	stack *ptr;
	int x;
		x = (*stk)->data;
		ptr = *stk;
		(*stk) = (*stk)->next;
		free(ptr);
		return x;
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
		printf("\n %d", stk->data);
	else
		printf("\n Stack Empty!");
}

/*
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
*/
