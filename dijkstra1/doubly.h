/*
File Name	: doubly.h
Description	: Function Declarations to implement a doubly linked list
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: October 17, 2017
*/

struct node
{
	int data;
	struct node prev;
	struct node next;
};

struct doubly
{
	struct node *head;
	struct node *tail;
	int length;
};

void createDoubly(struct doubly *list);
void addHead(struct doubly *list, data);
void addTail(struct doubly *list, data);
void addAfter(struct doubly *list, data, find);
void addBefore(struct doubly *list, data, find);
int delHead(struct doubly *list);
int delTail(struct doubly *list);
int delNode(struct doubly *list, data);
