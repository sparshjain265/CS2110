/*
Program Name: Ex4.c
Description	: Checks for a palindrom (Using recursion)
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: August 22, 2017
*/

#include<stdio.h>
#include<string.h>

//Function pal which takes a string and number of characters in it as input, returns 1 if palindrome, 0 if not
int pal(char *s, int n);

int main()
{	
	char str[25];
	
	//Taking a string from the user
	printf("Enter a string: ");
	scanf(" %24[^\n]s", str);
	
	//passing the string and it's length to the function and checking the output: Printing message accordingly
	if(pal(str, strlen(str)))
		printf("\n Congratulations! You have found a palindrome.");
	else
		printf("\n Sorry, %s is not a palindrome.", str);

	printf("\n\n");
	return 0;
}

////Defining function pal
int pal(char *s, int n)
{	
	//If there is only 1 character, it is a palindrome
	if(n == 1)
		return 1;
	//If there are two characters, it is a palindrome if they are same
	if(n == 2)
	{
		if(s[0] == s[1])
			return 1;
		else return 0;
	}
	//In case of more characters, the string is palindrome if first and last characters are same and the substing between them is also a palindrome
	if(s[0] == s[n-1])
		return pal(&s[1], n-2);	//Recursive call
	return 0;
}
