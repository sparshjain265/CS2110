/*
File Name	: graph.c
Description	: file to store common function definitions used to manipulate graphs in graph.c
Programmer	: Sparsh Jain
Roll 	No		: 111601026
Date			: October 17, 2017
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"queue.h"
#include"graph.h"


void color()
{
	int i;
	colors = (char **)calloc(4, sizeof(char *));
	for(i = 0; i < 10; i++)
		colors[i] = (char *)calloc(31, sizeof(char));
	
	strcpy(colors[0], "white");
	strcpy(colors[1], "red");
	strcpy(colors[2], "green");
	strcpy(colors[3], "blue");
}

//Function Definition to read the adjecency matrix format of graph file and return the graph as structured AM
//Takes pointer to the adjecency matrix format file of the graph
//Returns structured AM graph with proper details
struct AM readAdj(FILE *adj)
{
	struct AM graph;
	char c;
	int i, j;
	
	fscanf(adj, " %100[^\n]s", graph.name);											//storing the name of the graph
	fscanf(adj, " %5[^\n]s", graph.type);												//storing the format of the graph
	if(graph.type[0] != 'A' || graph.type[1] != 'M')								//If the format is not "AM" setting the size as -1 and returning
	{
		graph.size = -1;
		return graph;
	}
	
	fscanf(adj, " %d", &graph.size);											//storing the size of the graph
	graph.matrix = (int **)calloc(graph.size, sizeof(char *));		//Assigning appropriate memory for the matrix
	for(i = 0; i < graph.size; i++)
		graph.matrix[i] = (int *)calloc(graph.size, sizeof(char));
	
	for(i = 0; i < graph.size; i++)											//Reading the matrix from the text file character by character
	{
		fscanf(adj, "%c", &c);													//Accounting for newline character before entering a new row
		for(j = 0; j < graph.size; j++)
		{
			fscanf(adj, "%c", &c);
			graph.matrix[i][j] = (int)(c - 32);								//Storing the values in matrix
		}
	}
		
	return graph;																	//Returning after successful completion of the function
}

//Function Definition to write a dot format of the graph file from structure AM
//Takes pointer to the dot file and the structured adjacency matrix as input
//Writes the dot format of the graph in the file according to the adjacency matrix
void makeDot(FILE *dot, struct AM graph)
{
	int i, j, count;									
	fprintf(dot, "graph %s{\n", graph.name);			//printing the name of the graph in 1st line
	for(i = 0; i < graph.size; i++)						//Looping through the rows of the adjacency matrix
	{
		count = 0;												//count stores number of edges from the given row(node) which has not been counted yet; setting initially to zero
		for(j = i; j < graph.size; j++)					//looping through the upper half triangle of the matrix to avoid duplication
		{
			if(graph.matrix[i][j] != 0)					//If i & j have an edge, print in the dot file and increase the count
			{
				if(graph.matrix[i][j] < 10)
					fprintf(dot, "\t%d -- %d [label = %d];\n", i, j, graph.matrix[i][j]);
				else
					fprintf(dot, "\t%d -- %d [label = %d, color = %s];\n", i, j, graph.matrix[i][j] - 10, "red");
				count++;
			}
		}
		if(count == 0)											//If no new edge appears, print the node itself. Important to include isolated nodes
			fprintf(dot, "\t%d ;\n", i);		
	}
	fprintf(dot, "}");										//printing the closing braces in the last line
}

//Function Definition to use Breadth First Search method to find a path between two nodes
//Takes structured AM graph, and the two nodes as input
//Returns NULL if path is not found, a pointer to array which contains how we reached a visited node otherwise
int* BFS(struct AM graph, int root, int goal)
{
	int *visited, *previous;
	int i, current;
	struct queue toExplore;
	
	//Initializing empty list (visited)
	visited = (int *)calloc(graph.size, sizeof(int));
	for(i = 0; i < graph.size; i++)
		visited[i] = 0;
	
	//Initializing previously visited node from that node as -1 ie not visited
	previous = (int *)calloc(graph.size, sizeof(int));
	for(i = 0; i < graph.size; i++)
		previous[i] = -1;
	
	//Initializing empty queue toExplore
	toExplore.front = NULL;
	toExplore.rear = NULL;

	
	//If root and goal are same, path is found
	if(root == goal)
	{
		free(visited);										//Free the dynamically allocated memory before returning from the function
		previous[goal] = root;
		return previous;
	}
	else	
	{
		visited[root] = 1;								//Mark root as visited
		enqueue(&toExplore, root);						//Enqueue root to explore further
		while(isempty(toExplore) == 0)				//while the queue is not empty, search for a path
		{
			current = dequeue(&toExplore);			//set current node
			for(i = 0; i < graph.size; i++)			//traverse through 'current'th row(node)
			{
				if(graph.matrix[current][i] != 0)	//If it has an edge to ith column(node)
				{
					if(i == goal)							//If i is goal, free memory, and return 1
					{
						free(visited);
						while(isempty(toExplore) == 0)
							dequeue(&toExplore);
						previous[i] = current;			//Recording how we reached this node by storing the node previous to it
							
						return previous;
					}
					if(visited[i] == 0)					//Else if i is not visited, mark as visited and enqueue to explore further
					{
						visited[i] = 1;
						enqueue(&toExplore, i);
						previous[i] = current;			//Recording how we reached this node by storing the node previous to it
					}
				}	
			}
		}
	}
	
	free(visited);												//Free the dynamically allocated memory before returning from the function
	return NULL;												//Function will reach here if no path is found. Return 0
}

//Function Definition to count the number of components in the graph
//Takes structured AM graph as input
//Returns the number of components as output
int count(struct AM graph)
{
	int *visited, u = 0, v = 0, *previous, components = 0, i, j;
	
	//Dynamic array to check whether a vertex is visited or not, initially set to 0
	visited = (int *)calloc(graph.size, sizeof(int));
	for(i = 0; i < graph.size; i++)
		visited[i] = 0;
	
	//Nested loop to check the connectivity between 2 vertices
	for(i = 0; i < graph.size; i++)
	{
		for(j = i; j < graph.size; j++)
		{
			//If not already visited, check if connected
			if(visited[j] == 0)
			{
				previous = BFS(graph, i, j);
				//If found connected, mark visited
				if(previous != NULL)
				{
					visited[j] = 1;
					v++;
				}
			}
		}
		//If visited vertices increase from a new vertex, increase the number of components by 1
		if(u < v)
		{
			components++;
			u = v;
		}
	}
	
	//Return the number of components
	return components;	
}

//Function Definition to color the path between root and goal
//Takes pointer to the path array, root, goal, graph and the color as input
//Updates the edge from 1 to 2 to color it red
void colorPath(int *previous, int root, int goal, struct AM graph, int color)
{
	int current = goal;												//Starting from goal
	
	if(root == goal)													//If root is the goal, no coloring required
		return;
	
	while(previous[current] != root)								//Color the edge until previous node is not root
	{
		graph.matrix[current][previous[current]] = color;
		graph.matrix[previous[current]][current] = color;
		current = previous[current];
	}
	graph.matrix[current][previous[current]] = color;			//Color the last edge
	graph.matrix[previous[current]][current] = color;	
	
}

//Function Definition to print a path between 2 nodes in a graph
//Takes pointer to the path array, root, goal, and the size of graph as input
//Prints the path on screen and returns the distance
int printPath(int *previous, int root, int goal, int size)
{
	int current, *path, i, distance = 0;
	
	//Initializing the dynamic path array
	path = (int *)calloc(size, sizeof(int));
	for(i = 0; i < size; i++)
		path[i] = -1;
	
	//Updating the path array according to the array given 
	current = goal;
	for(i = 0; current != root; i++)
	{
		path[i] = current;
		current = previous[current];
	}
	path[i] = current;	//Adding the root to the path array
	
	//Updating the distance
	distance = i;
	
	//Printing the path
	printf("\n");
	for(i = distance; i > 0; i--)
		printf(" %d -->", path[i]);
	printf(" %d", path[i]);
	
	//Freeing the dynamically allocated memory
	free(path);
	
	//Returning the distance
	return distance;
}

//Function Definition to return the length of a path
//Takes pointer to the path array, root, goal, and the size of graph as input
//returns the distance
int distance(int *previous, int root, int goal, struct AM graph)
{
	int current, *path, i, distance = 0;
	
	//Initializing the dynamic path array
	path = (int *)calloc(graph.size, sizeof(int));
	for(i = 0; i < graph.size; i++)
		path[i] = -1;
	
	//Updating the path array according to the array given 
	current = goal;
	for(i = 0; current != root; i++)
	{
		path[i] = current;
		current = previous[current];
		distance = distance + graph.matrix[current][previous[current]] - 10;
	}
	path[i] = current;	//Adding the root to the path array
	
	//Freeing the dynamically allocated memory
	free(path);
	
	//Returning the distance
	return distance;
}

