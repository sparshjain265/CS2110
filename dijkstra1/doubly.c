/*
File Name	: doubly.h
Description	: Function Definitions to implement a doubly linked list
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: October 17, 2017
*/

void createDoubly(struct doubly *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
}

void addHead(struct doubly *list, data)
{
	struct node *ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->prev = NULL;
	ptr->next = NULL;
	if(list->length == 0)
		list->head = list->tail = ptr;
	else
	{
		ptr->next = list->head;
		list->head->prev = ptr;
		list->head = ptr;
	}
	list->length++;
}

void addTail(struct doubly *list, data)
{
	struct node *ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->prev = NULL;
	ptr->next = NULL;
	if(list->length == 0)
		list->head = list->tail = ptr;
	else
	{
		ptr->prev = list->tail;
		list->tail->next = ptr;
		list->tail = ptr;
	}
	list->length++;
}

void addAfter(struct doubly *list, data, find)
{
	struct node *ptr = (struct node *)malloc(sizeof(struct node)), *p;
	ptr->data = data;
	ptr->prev = NULL;
	ptr->next = NULL;
	
	p = list->head;
	while(p != NULL)
	{
		if(p->data == find)
		{
			ptr->prev = p;
			ptr->next = p->next;
			if(p->next != NULL)
				p->next->prev = ptr;
			else
				list->tail = ptr;
			p->next = ptr;
			list->length++;
			return;
		}
		p = p->next;
	}
	printf("\n %d not found!\n %d not added!", find, data);
}

void addBefore(struct doubly *list, data, find)
{
	struct node *ptr = (struct node *)malloc(sizeof(struct node)), *p;
	ptr->data = data;
	ptr->prev = NULL;
	ptr->next = NULL;
	
	p = list->head;
	while(p != NULL)
	{
		if(p->data == find)
		{
			ptr->next = p;
			ptr->prev = p->prev;
			if(p->prev != NULL)
				p->prev->next = ptr;
			else
				list->head = ptr;
			p->prev = ptr;
			list->length++;
			return;
		}
		p = p->next;
	}
	printf("\n %d not found!\n %d not added!", find, data);
}

int delHead(struct doubly *list)
{
	struct node *ptr = list->head;
	int data;
	if(list->length == 0)
	{
		printf("\n Nothing to delete! Returning -1!");
		return -1;
	}
	if(list->length == 1)
	{
		list->head = list->tail = NULL;
		list->length--;
		data = ptr->data;
		free(ptr);
		return data;
	}
	list->head = list->head->next;
	list->head->prev = NULL;
	list->length--;
	data = ptr->data;
	free(ptr);
	return data;	
}

int delTail(struct doubly *list)
{
	struct node *ptr = list->tail;
	int data;
	if(list->length == 0)
	{
		printf("\n Nothing to delete! Returning -1!");
		return -1;
	}
	if(list->length == 1)
	{
		list->head = list->tail = NULL;
		list->length--;
		data = ptr->data;
		free(ptr);
		return data;
	}
	list->tail = list->tail->prev;
	list->tail->next = NULL;	
	list->length--;
	data = ptr->data;
	free(ptr);
	return data;
}

int delNode(struct doubly *list, data)
{
	struct node *ptr = list->head;
	if(list->length == 0)
	{
		printf("\n Nothing to delete! Returning -1!");
		return -1;
	}
	
	while(ptr != NULL)
	{
		if(ptr->data == data)
		{
			if(list->head == ptr)
				list->head = ptr->next;
			if(list->tail == ptr)
				list->tail = ptr->prev;
			if(ptr->next != NULL)
				ptr->next->prev = ptr->prev;
			if(ptr->prev != NULL)
				ptr->prev->next = ptr->next;
			list->length--;
			free(ptr);
			return data;
		}
		else ptr = ptr->next;
	}
	
	printf("\n %d not found!\n Nothing deleted!\n Returning -1", data);
	return -1;
}






















