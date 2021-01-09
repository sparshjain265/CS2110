/*
Program Name:	prep.c
Description	: 	Preparation for Excercise Set 3b
Programmer	:	Sparsh Jain
Roll No		: 	111601026
Date			: 	September 12, 2017
*/

#include<stdio.h>
#include<stdlib.h>

int * mergeSort(int *a, int n);
int * merge(int *x, int *y, int a, int b);

void quickSort(int *a, int n, int left, int right);
int part(int *a, int n, int left, int right, int pivot);

void bubbleSort(int *a, int n);

int main()
{
	int *a, n, i, left, right;

	printf("\n Enter n: ");
	scanf(" %d", &n);	
	a = (int *)calloc(n, sizeof(int));

	
	for(i = 0; i < n; i++)
	{
		printf("\n Enter data #%d: ", i+1);
		scanf(" %d", &a[i]);
	}
	
	//a = mergeSort(a, n);
	
	/*
	left = 0;
	right = n-1;
	quickSort(a, n, left, right);
	*/
	
	bubbleSort(a, n);
	
	printf("\n Sorted List: ");
	for(i = 0; i < n; i++)
		printf(" %d", a[i]);
		
	free(a);
	
	printf("\n\n");
	return 0;
}

void bubbleSort(int *a, int n)
{
	int i, j, tmp;
	
	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-i-1; j++)
		{
			if(a[j] > a[j+1])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
	
}

void quickSort(int *a, int n, int left, int right)
{
	int pivot, partition;
	
	if(right - left <= 0)
		return;
	
	pivot = a[left];
	partition = part(a, n, left, right, pivot);
	quickSort(a, right - left, left, partition - 1);
	quickSort(a, right - left, partition + 1, right);
}

int part(int *a, int n, int left, int right, int pivot)
{
	int l = left + 1, r = right, tmp;
	
	while(1)
	{
		while(a[l] < pivot)
			l++;
		while(a[r] > pivot)
			r--;
		if(l >= r)
			break;
		else 
		{
			tmp = a[l];
			a[l] = a[r];
			a[r] = tmp;
		}
	}
	
	tmp = a[left];
	a[left] = a[r];
	a[r] = tmp;
	
	return r;
}

int * mergeSort(int *a, int n)
{
	int *x, *y, i;
	if(n == 1)	return a;
	
	x = (int *)calloc(n/2, sizeof(int));
	y = (int *)calloc(n - n/2, sizeof(int));
	
	for(i = 0; i < n/2; i++)
		x[i] = a[i];
	for(; i < n; i++)
		y[i - n/2] = a[i];
		
	x = mergeSort(x, n/2);
	y = mergeSort(y, n - n/2);
	
	free(a);
	
	return merge(x, y, n/2, n - n/2);	
	
}

int * merge(int *x, int *y, int a, int b)
{
	int *c, i = 0, j = 0;
	
	c = (int *)calloc(a + b, sizeof(int));
	
	while(i < a && j < b)
	{
		if(x[i] < y[j])
			c[i+j] = x[i++];
		else 
			c[i+j] = y[j++];
	}
	while(i < a)
		c[i+j] = x[i++];
	while(j < b)
		c[i+j] = y[j++];
	
	free(x);
	free(y);
	
	return c;	
}






























