/*
File Name	: main.c
Description	: contains the main function to find the shortest path in a weighted graph
Programmer	: Sparsh Jain
Roll No		: 111601026
Date			: October 31, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graph.h"

int* weightedPath(struct AM graph, int x, int y);								//Function Declaration to find the shortest weighted path 
void editGraph(struct AM *graph, int *path, int x, int y);					//Function Declaration to edit the matrix for dotted edges

int main()
{
	FILE *adj, *dot;
	char adjName[31], dotName[31];
	struct AM graph;
	int *path, x, y, l;								
	
	//Reading the file name from the user until it can be opened
	while(1)
	{
		printf("\n Enter the name of the (Adjecency Matrix) file : ");
		scanf(" %s", adjName);
		adj = fopen(adjName, "r");
		if(adj == NULL)
			printf("\n File Not Found! Try Again!");
		else
			break;
	}
	
	strcpy(dotName, adjName);
	l = strlen(dotName);
	dotName[l-3] = 'd';
	dotName[l-2] = 'o';
	dotName[l-1] = 't';
	dot = fopen(dotName, "w");																						//Opening a file to create dot file
	
	graph = readAdj(adj);																							//Reading the adjacency matrix
	
	//Asking for input
	printf("\n Enter x: ");
	scanf(" %d", &x);
	printf("\n Enter y: ");
	scanf(" %d", &y);	
		
	path = weightedPath(graph, x, y);																				//Finding the shortest weighted path
	//If no path is found, abort program
	if(path == NULL)
	{
		printf("\n %d and %d do not have a path!", x, y);
		//Closing opened files and freeing dynamic memory
		fclose(adj);
		fclose(dot);
		free(graph.matrix);
		printf("\n\n");
		return 0;
	}
	editGraph(&graph, path, x, y);																						//Editiing the matrix for red edges
	makeDot(dot, graph);																									//Making the dot file
	
	//Printing the distance and path
	printf("\n Distance between %d and %d = %d", x, y, distance(path, x, y, graph));
	printf("\n Shortest path between %d and %d with least number of blue edges: ", x, y);
	printPath(path, x, y, graph.size);
	printf("\n %s created.", dotName);
	
	
	//Closing opened files and freeing dynamic memory
	fclose(adj);
	fclose(dot);
	free(graph.matrix);
	printf("\n\n");
	return 0;
}

//Function Definition to edit the graph to color the shortest weighted path as red
//Takes pointer to the structured graph, pointer to the path, and start and end points as inputs
//Increments the value in the adjacency matrix by 10 to indicate the path
void editGraph(struct AM *graph, int *path, int x, int y)
{	
	//Starting from the goal
	int current = y;
	
	//Working upwards till it reaches the source
	while(current != x)
	{
		//Incrementing by 10
		(*graph).matrix[current][path[current]] += 10;
		(*graph).matrix[path[current]][current] += 10;
		current = path[current];
	}
	
}

//Function Definition to find the shortest weighted path
//Takes structured graph, start and end points as inputs
//Returns pointer to the path from x to y
int* weightedPath(struct AM graph, int x, int y)
{
	int *dist, *prev, *vis, i, check = 1, current = x, temp, min, minDist;
	
	//Allocating required amount of memory
	dist = (int *)calloc(graph.size, sizeof(int));
	prev = (int *)calloc(graph.size, sizeof(int));
	vis = (int *)calloc(graph.size, sizeof(int));

	//Initializing arrays accordingly
	for(i = 0; i < graph.size; i++)
	{
		//printf("\n i1 = %d \n", i);
		dist[i] = 10*graph.size;
		prev[i] = -1;
		vis[i] = 0;
	}
	
	//Distance of the starting node is 0
	dist[x] = 0;
	
	//While 'check' is fulfilled, continue
	while(check == 1)
	{
		//printf("\n current = %d\n", current);
		//Mark current as visited
		vis[current] = 1;
		for(i = 0; i < graph.size; i++)
		{
			//If a non visited vertex has an edge with current
			if(graph.matrix[current][i] != 0 && vis[i] != 1)
			{
				//printf("\n i2 = %d \n", i);
				//comparing the distance of the vertex and it's previous node as required
				temp = dist[current] + graph.matrix[current][i];
				if(temp < dist[i])
				{
					dist[i] = temp;
					prev[i] = current;
				}
			}
		}
		
		//Assuming 'check' is not satisfied
		check = 0;
		//Check is satisfied if there is an unvisited vertex reachable from the source
		min = graph.size;
		minDist = 10*graph.size;
		for(i = 0; i < graph.size; i++)
		{
			//printf("\n i3 = %d ", i);
			if(vis[i] == 0 && dist[i] < minDist)
			{
				min = i;
				minDist = dist[i];
				check = 1;
			}
		}
		//Current is set to be the unvisited vertex with shortest distance from the source
		current = min;
		//If current is the target, we're done, break the loop
		if(current == y)
			break;
	}
	
	//Free the dynamically allocated memory
	
	free(vis);													///////////////////////////////////Some memory leak in visited : Yet to find 
	free(dist);

	//If y is not reachable from x return NULL, else return path in the form of prev array
	if(prev[y] == -1)
		return NULL;
	else return prev;
}

