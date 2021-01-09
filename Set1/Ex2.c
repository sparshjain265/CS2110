/*
Program Name	: Ex2.c 
Description		: Exercise 1 - Q2
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: August 1, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Creating structure 'student' with members, a string variable name and an integer variable ID
struct student
{
	char name[25];
	int ID;
};

//Declaring the functions PrintStruc and ChangeStruc
void PrintStruc(struct student s);
void ChangeStruc(struct student *s);

int main()
{
	//Declaring required variables
	struct student *list;
	int N, i, large, l;
	
	//Taking the number of students in N
	printf("\n Enter the number of Students: ");
	scanf(" %d", &N);
	
	//Dynamically Allocating Memory to the structure pointer
	list = (struct student*)calloc(N, sizeof(struct student));
	
	//continue if memory is allocated
	if(list != NULL)
	{	
		//Taking input of the student name and ID
		for(i = 0; i < N; i++)
		{
			printf("\nEnter Name of Student #%d: ", i+1);
			scanf(" %[^\n]s", list[i].name);
			printf("\nEnter ID: ");
			scanf(" %d", &list[i].ID);
		}
	
		//Finding the largest ID
		large = list[0].ID;
		l = 0;
		for(i = 1; i < N; i++)
		{
			if(list[i].ID > large)
			{
				large = list[i].ID;
				l = i;
			}
		}
	
		//Printing the largest ID
		printf("\n Student with largest ID:-");
		PrintStruc(list[l]);
	
		//Deallocating the memory
		free(list);
	}
	//else print an error message
	else
	{
		printf("\n Not enough memory!");
	}
	
	printf("\n\n");
	return 0;
}

//Defining function PrintStruc to print the contents of student type structure
//Takes a struct student type arguement
void PrintStruc(struct student s)
{
	printf("\n Name: %s", s.name);
	printf("\n ID: %d", s.ID);
}

//Defining function ChangeStruc to change the contents of student type structure
//Takes a struct student pointer as arguement
void ChangeStruc(struct student *s)
{
	strcpy(s->name, "abc");
	s->ID = 123;
}









