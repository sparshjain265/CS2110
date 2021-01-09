/*
Serial No	: B
Question No	: Q2
Program Name: problem2.c
Programmer	: Sparsh Jain
Roll No		: 111601026
IP address	: 10.64.1.168
Description	: Employee Register
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Defining node for a queue
struct node
{
	char *name;
	struct node *next;
	
};

void create(struct node *start, struct node *last);//Function create to initialize a queue with first and last pointer as NULL
void enqueue(struct node *last, char *name);			//Function enqueue to enqueue a member at the end of the queue
char * dequeue(struct node *start);						//Function dequeue to dequeue a member from the front of the queue
int isempty(struct node *start);							//Function isempty to check whether a queue is empty or not

void printMenu();												//Function printMenu to print the Menu

int main()
{
	int i, choice;
	char *name, *n;
	struct node *start, *end, *front, *back;		
	
	//Creating 2 queues, start-end and front-back
	create(start, end);
	create(front, back);
	
	//Infinite Loop until user chooses to exit the program
	while(1)
	{
		//Printing the menu and asking for the choice
		printMenu();
		printf("\n Enter your choice: ");
		scanf(" %d", &choice);
		//Invoking switch to implement the choice
		switch(choice)
		{
			case 1:	//Hire
						//If start is empty, enter in start
						if(isempty(start))
						{
							printf("\n Enter the name of the new Employee (max 30 characters): ");
							name = (char *)calloc(31, sizeof(char));
							scanf(" %30s", name);
							enqueue(end, name);			//Enqueue in the end (of start)
							start = end;					//Since it has only 1 element right now, start = end
							end->next = front;			//Merging (front) in the end (of start)
							end = back;						//Updating the end
							front = back = NULL;			//Setting front-back as empty
							break;
						}
						else	//else enter in front by same logic
						{
							printf("\n Enter the name of the new Employee (max 30 characters): ");
							scanf(" %30s", name);
							enqueue(back, name);
							front = back;
							back->next = start;
							back = end;
							start = end = NULL;
							break;
						}						
			case 2: 	//Fire
						//If both the queues are empty, there is no one to fire
						if(isempty(start) && isempty(front))
						{
							printf("\n No Employee to fire!");
							break;
						}
						//If start is not empty, fire from start
						if(!isempty(start))
						{
							if(n != NULL)			
								free(n);
							n = dequeue(start);
							printf("\n %s fired!", n);
							break;
						}
						//Else front is empty, fire from front
						else
						{
							if(n != NULL)
								free(n);
							n = dequeue(front);
							printf("\n %s fired!", n);
							break;
						}
			case 3: 	//Display
						if(isempty(start) && isempty(front))
							printf("\n No Employee works for you!");
						if(!isempty(start))
						{
							i = 0;
							while(!isempty(start))
							{
								if(n != NULL)
									free(n);
								n = dequeue(start);
								enqueue(back, n);
								if(i == 0)
									front = back;
								printf("\n %s works for you.", n);
								i++;
							}
						}
						else
						{
							i = 0;
							while(!isempty(front))
							{
								if(n != NULL)
									free(n);
								n = dequeue(front);
								enqueue(end, n);
								if(i == 0)
									start = end;
								printf("\n %s works for you.", n);
								i++;
							}
						}
						break;
			case 4: 	//Exit
						while(!isempty(start))
							n = dequeue(start);
						while(!isempty(front))
							n = dequeue(front);
						if(n != NULL)
							free(n);
						if(name != NULL)
							free(name);
						printf("\n\n");
						return 0;
			default: //Unsupported Input
						printf("\n Incorrect Choice! Try Again!");
						choice = -1;
		}
	}
	
}

//Function Definition to create a queue
//Takes front and last pointers as input
//Sets them to NULL
void create(struct node *start, struct node *last)
{
	start = last = NULL;
}

//Function definition to enqueue
//Takes pointer to the last and pointer to string name as input
//Enqueues the new pointer at the back of the last, then updates the last pointer
void enqueue(struct node *last, char *name)
{
	struct node *ptr;
	ptr = (struct node *)malloc(sizeof(struct node));	//Allocating Required Memory
	ptr->name = name;
	ptr->next = NULL;												//Since this has to be last entry, setting next to NULL
	if(last != NULL)												//If last is not NULL, setting the next of last to the new node
		last->next = ptr;
	last = ptr;														//Updating the last to the new node
}


//Function definition to dequeue
//Takes pointer to the front as input
//Returns name of the fired employee
char * dequeue(struct node *start)				
{
	char *name;											
	struct node *ptr;
	name = (char *)calloc(31, sizeof(char));				//Allocating Required memory
	ptr = start;													//Setting ptr as the front
	start = start->next;											//Forwarding the front
	strcpy(name, ptr->name);									//Copying name from ptr
	free(ptr);														//Freeing memory to prevent memory leak
	return name;													//Returning pointer to string name
}

//Function definition to check if a queue is empty
//Takes pointer to the front as input
//Returns 1 if empty, 0 if not
int isempty(struct node *start)
{
	if(start == NULL)												//If front is NULL, it means the queue is empty, return 1
		return 1;
	else return 0;													//Else return 0
}

//Function definition to print the menu
void printMenu()
{
	printf("\n \t Menu ");
	printf("\n 1. Hire ");
	printf("\n 2. Fire ");
	printf("\n 3. Display ");
	printf("\n 4. Exit ");
}

