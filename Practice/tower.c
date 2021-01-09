/*
Program Name: tower.c
Description	: Program to show the steps to win Tower of Hanoi in minimum number of steps
Programmer	: Sparsh Jain
Roll 	No		: 111601026
Date			: September 19, 2017
*/

#include<stdio.h>

//Function Declarations
int tower(int n, int source, int help, int target, int steps);	//Function tower: Shows the steps required to win the Tower of Hanoi in minimum number of steps

int main()
{
	//Declaring and initializing variables
	//In the beginning, number of steps = 0, source tower = 1, help tower = 2, and target tower = 3
	int n, steps = 0, source = 1, help = 2, target = 3;
	
	//Taking the number of disks in the source tower from the user
	printf("\n Enter the number of disks in Tower #%d: ", source);
	scanf(" %d", &n);
	
	//Calling the function tower and updating the number of steps taken
	steps = tower(n, source, help, target, steps);
	
	//Printing the number of steps taken if valid
	if(steps > -1)
		printf("\n Completed in %d steps. ", steps);
	
	printf("\n\n");
	return 0;
}

//Function Definitions
//Function tower: Shows the steps required to win the Tower of Hanoi in minimum number of steps
//Takes number of disks, label of source, help, and target towers, and number of steps already taken
//Returns the updated number of steps
int tower(int n, int source, int help, int target, int steps)
{
	if(n<0)	//If the number of disks is less than 0, print error message and return -1
	{
		printf("\n Invalid Tower!");
		return -1;
	}
	if(n==0)	//If the number of disks is 0, game is won. return 0
		return 0;
	if(n==1)	//If the number of disks is 1, move disk from target to source, increment and return steps
	{
		printf("\n Move disk from Tower #%d to Tower #%d.", source, target);
		steps++;
		return steps;
	}
	//Program will reach here only if the number of disks is more than 1
	steps = tower(n-1, source, target, help, steps);							//Move top n-1 disks from source to help and update the number of steps
	printf("\n Move disk from Tower #%d to Tower #%d.", source, target);	//Move the nth disk from source to target and increment steps
	steps++;
	steps = tower(n-1, help, source, target, steps);							//Move n-1 disks from help to target and return the updated the number of steps
	return steps;																			
}
