/*
File Name	: graph.h
Description	: file to store common function declarations and data structures used to manipulate graphs in graph.c
Programmer	: Sparsh Jain
Roll 	No		: 111601026
Date			: October 17, 2017
*/

//Structure AM to store Adjacent Matrix form of a graph
struct AM
{
	char name[101];
	char type[6];
	int **matrix;
	int size;
};

char **colors;

struct AM readAdj(FILE *adj);																			//Function Declaration to read the adjecency matrix format of graph file and return the graph as structure AM
void makeDot(FILE *dot, struct AM graph);															//Function Declaration to write a dot format of the graph file from structure AM
int* BFS(struct AM graph, int root, int goal);													//Function Declaration to use Breadth First Search method to find a path between two nodes
int count(struct AM graph);																			//Function Declaration to count the number of components in the graph
void colorPath(int *previous, int root, int goal, struct AM graph, int color);		//Function Declaration to color the path between root and goal
int printPath(int *previous, int root, int goal, int size);									//Function Declaration to print a path between 2 nodes in a graph
int distance(int *previous, int root, int goal, struct AM graph);                 	//Function Declaration to return the path length
void color();																								//Function Declaration to initialize colors
