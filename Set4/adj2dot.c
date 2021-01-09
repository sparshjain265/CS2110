/*
Program Name:	adj2dot.c
Description	: 	Program to convert adjecency matrix form of a graph to dot format
Programmer	: 	Sparsh Jain
Roll No		: 	111601026
Date			: 	October 3, 2017
*/

#include<stdio.h>
#include<stdlib.h>

//structure AM (stands for Adjecency Matrix) to store the details of the graph (it's name, adjecency matrix and size)
struct AM
{
	char name[31], **matrix;
	int size;
};

struct AM readAdj(FILE *adj);					//Function Declaration to read the adjecency matrix format of graph file and return the graph as structure AM
void makeDot(FILE *dot, struct AM graph);	//Function Declaration to write a dot format of the graph file from structure AM

int main()
{
	FILE *adj, *dot;
	char adjName[31], dotName[31];
	struct AM graph;
	
	//Reading the file name from the user until it can be opened
	while(1)
	{
		printf("\n Enter the name of the (Adjecency Matrix) file you want to convert in DOT Format : ");
		scanf(" %s", adjName);
		adj = fopen(adjName, "r");
		if(adj == NULL)
			printf("\n File Not Found! Try Again!");
		else
			break;
	}
	
	//Reading the output file name from the user until it can be opened
	while(1)
	{
		printf("\n Enter the name of the dot file you want to save as (ending with .dot) : ");
		scanf(" %s", dotName);
		dot = fopen(dotName, "w");
		if(dot == NULL)
			printf("\n Could not create file! Try Again!");
		else
			break;
	}
	
	//Calling functions readAdj and makeDot to read the AM format and covert them to dot file
	graph = readAdj(adj);
	makeDot(dot, graph);
	
	//closing files and freeing dynamic memory
	fclose(adj);
	fclose(dot);
	free(graph.matrix);
	printf("\n\n");
	return 0;
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
			if(graph.matrix[i][j] == '1')					//If i & j have an edge, print in the dot file and increase the count
			{
				fprintf(dot, "\t%d -- %d ;\n", i, j);
				count++;
			}
		}
		if(count == 0)											//If no new edge appears, print the node itself. Important to include isolated nodes
			fprintf(dot, "\t%d ;\n", i);		
	}
	fprintf(dot, "}");										//printing the closing braces in the last line
}

//Function Definition to read the adjecency matrix format of graph file and return the graph as structure AM
//Takes pointer to the adjecency matrix format file of the graph
//Returns structured AM graph with proper details
struct AM readAdj(FILE *adj)
{
	struct AM graph;
	char format[3], c;
	int i, j;
	
	fscanf(adj, " %30[^\n]s", graph.name);									//storing the name of the graph
	fscanf(adj, " %3[^\n]s", format);										//storing the format of the graph
	if(format[0] != 'A' || format[1] != 'M')								//If the format is not "AM" setting the size as -1 and returning
	{
		graph.size = -1;
		return graph;
	}
	
	fscanf(adj, " %d", &graph.size);											//storing the size of the graph
	graph.matrix = (char **)calloc(graph.size, sizeof(char *));		//Assigning appropriate memory for the matrix
	for(i = 0; i < graph.size; i++)
		graph.matrix[i] = (char *)calloc(graph.size, sizeof(char));
	
	for(i = 0; i < graph.size; i++)											//Reading the matrix from the text file character by character
	{
		fscanf(adj, "%c", &c);													//Accounting for newline character before entering a new row
		for(j = 0; j < graph.size; j++)
		{
			fscanf(adj, "%c", &graph.matrix[i][j]);						//Storing the values in matrix
		}
	}
		
	return graph;																	//Returning after successful completion of the function
}
