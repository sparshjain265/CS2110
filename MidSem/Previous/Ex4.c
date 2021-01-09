/*
Program Name	: Ex4.c
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
	char data;
	struct stack *next;
};

//typedef for our convinience
typedef struct stack stack;

stack * newStack();								//Function to create a new stack, returns pointer to the new stack
void stackPush(stack **stk, char x);	//Function to push an element in the stack, takes a pointer to stack and the data as input
char stackPop(stack **stk);					//Function to pop an element from the stack, takes a pointer to stack as input, returns data or error message as output
int stackIsEmpty(stack *stk);					//Function to check whether the stack is empty, takes a stack pointer, returns 0 if stack is empty
char stackTop(stack *stk);						//Function to print the topmost element of the stack, takes a stack pointer as input
//void printMenu();									//Function to print the menu of the program

int main()
{
	//Declaring required variables
	int i, length = -1;
	char data;
	char d[50];
	//Creating new stack called myStack
	stack *myStack = newStack();
    //Asking user for infix format
    printf("\n Enter Infix: ");
    scanf(" %49[^\n]s", d);
    printf("\n %s = ", d);
    //Loop continues until all the user-given characters are accounted for
    for(i = 0; i < strlen(d);)
    {   //Conversion is done according to the rules
        if(d[i] > 47 && d[i] < 58)
        {
            printf("%c", d[i]);
        }
        else if(d[i] == '+')
        {
            if(length == -1 || (stackTop(myStack) == '('))
            {
                stackPush(&myStack, d[i]);
                length++;
            }
            else if(stackTop(myStack) == '-' || stackTop(myStack) == '+')
            {
                data = stackPop(&myStack);
                printf("%c", data);
                stackPush(&myStack, d[i]);
            }
            else if(stackTop(myStack) == '*' || stackTop(myStack) == '/')
            {
                data = stackPop(&myStack);
                printf("%c", data);
                length--;
                continue;
            }
        }
        else if(d[i] == '-')
        {
            if(length == -1 || (stackTop(myStack) == '('))
            {
                stackPush(&myStack, d[i]);
                length++;
            }
            else if(stackTop(myStack) == '+' || stackTop(myStack) == '-')
            {
                data = stackPop(&myStack);
                printf("%c", data);
                stackPush(&myStack, d[i]);
            }
            else if(stackTop(myStack) == '*' || stackTop(myStack) == '/')
            {
                data = stackPop(&myStack);
                printf("%c", data);
                length--;
                continue;
            }
        }
        else if(d[i] == '*')
        {
            if(length == -1 || (stackTop(myStack) == '('))
            {
                stackPush(&myStack, d[i]);
                length++;
            }
            else if(stackTop(myStack) == '+' || stackTop(myStack) == '-')
            {
               stackPush(&myStack, d[i]);
               length++;
            }
            else if(stackTop(myStack) == '*' || stackTop(myStack) == '/')
            {
                data = stackPop(&myStack);
                printf("%c", data);
                stackPush(&myStack, d[i]);
            }
        }
        else if(d[i] == '/')
        {
            if(length == -1 || (stackTop(myStack) == '('))
            {
                stackPush(&myStack, d[i]);
                length++;
            }
            else if(stackTop(myStack) == '+' || stackTop(myStack) == '-')
            {
               stackPush(&myStack, d[i]);
               length++;
            }
            else if(stackTop(myStack) == '*' || stackTop(myStack) == '/')
            {
                data = stackPop(&myStack);
                printf("%c", data);
                stackPush(&myStack, d[i]);
            }
        }
        else if(d[i] == '(')
        {
            stackPush(&myStack, d[i]);
            length++;
        }
        else if(d[i] == ')')
        {
            data = stackPop(&myStack);
            length--;
            while(data != '(')
            {
                printf("%c", data);
                if(length == -1)
                {
                    printf("\n Invalid Expression!");   //If a left parenthesis is not found for a right parenthesis: given expression is invalid
                    while(stackIsEmpty(myStack))
                    {
                        data = stackPop(&myStack);
                        length--;
                    }
                    break;
                }
                data = stackPop(&myStack);
                length--;
            }
        }
        else
        {
            printf("\n Invalid Expression!");           //If a given character isn't a numeric digit or an arithmetic operation, give expression is invalid
            while(stackIsEmpty(myStack))
            {
                data = stackPop(&myStack);
                length--;
            }
            break;
        }
    i++;
    }
    //Printing the rest of the stack at the end: Automatically frees the memory
    while(stackIsEmpty(myStack))
    {
        data = stackPop(&myStack);
        length--;
        printf("%c", data);
    }
	printf("\n\n");
	return 0;
}

//Function definition to create a new stack
stack * newStack()
{
	stack *stk = NULL;
	return stk;
}

//Function Definition to push into stack
void stackPush(stack **stk, char x)
{
	stack *ptr;
	ptr = (stack *)malloc(sizeof(struct stack));
	ptr->data =  x;
	ptr->next = *stk;
	*stk = ptr;
}

//Function definition to pop from a stack
char stackPop(stack **stk)
{
	stack *ptr;
	char x;
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
char stackTop(stack *stk)
{
	if(stackIsEmpty(stk))
		return stk->data;
	else
		printf("\n Stack Empty!");
		return '\0';
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
