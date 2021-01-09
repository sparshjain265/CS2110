/*
Program Name	: Ex2.c 
Description		: Exercise 1 - Q1
Programmer		: Sparsh Jain
Roll No.			: 111601026
Date				: August 1, 2017
*/

#include<stdio.h>
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
	//Declaring a student structure stu1, and a student structure pointer srtptr
	struct student stu1, *srtptr;
	int i;
	
	//Initializing the structure stu1
	printf("\nEnter Student Name: ");
	scanf(" %[^\n]s", stu1.name);
	printf("\nEnter Student ID: ");
	scanf(" %d", &stu1.ID);
	
	//Printing structure stu1 using function PrintStruc
	PrintStruc(stu1);
	
	//Assigning and Passing stu1 through a structure pointer srtptr
	srtptr = &stu1;
	ChangeStruc(srtptr);
	
	//Printing the values of the structure using structure pointer
	PrintStruc(*srtptr);
	
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



