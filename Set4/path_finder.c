/*
Program Name:	path_finder.c
Description	: 	Program to check whether a path exists between 2 vertices in a graph of adjacency matrix format
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

//Structure node to implement queue with integer data 
struct node
{
	int data;
	struct node *next;
};

//Structure queue to implement queue
struct queue
{
	struct node *front;
	struct node *rear;
};

//Function Declarations for queue implementation
void enqueue(struct queue *q, int data);			
int dequeue(struct queue *q);
int isempty(struct queue q);

struct AM readAdj(FILE *adj);																//Function Declaration to read the adjecency matrix format of graph file and return the graph as structure AM
int* BFS(struct AM graph, int root, int goal);										//Function Declaration to use Breadth First Search method to find a path between two nodes
void makeDot(FILE *dot, struct AM graph);												//Function Declaration to write a dot format of the graph file from structure AM
void colorPath(int *previous, int root, int goal, struct AM graph);			//Function Declaration to color the path between root and goal
int printPath(int *previous, int root, int goal, int size);						//Function Declaration to print a path between 2 nodes in a graph
		
int main()
{
	FILE *adj, *dot;
	char adjName[31], dotName[31];
	int root, goal, *previous = NULL;
	struct AM graph;								
	
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
	
	//Calling function readAdj to read the file and store it as a structured data
	graph = readAdj(adj);
	
	//Asking the user for 2 nodes
	printf("\n Enter 2 nodes (< %d): ", graph.size);
	scanf(" %d%d", &root, &goal);
	
	//Calling BFS function and storing the path in path pointer
	previous = BFS(graph, root, goal);
	//If path is NULL means no path found, else print the path
	if(previous == NULL)
		printf("\n No path exists between %d and %d.", root, goal);
	else
	{
		printf("\n Yes! Following path exists between %d and %d.", root, goal);
		printPath(previous, root, goal, graph.size);
	}
	
	//Update the coloring of the path and create the dot file
	if(previous != NULL)
		colorPath(previous, root, goal, graph);
	makeDot(dot, graph);
	
	//Closing opened files and freeing dynamic memory
	fclose(adj);
	fclose(dot);
	free(graph.matrix);
	printf("\n\n");
	return 0;
}

//Function Definition to color the path between root and goal
//Takes pointer to the path array, root, goal and the graph as input
//Updates the edge from 1 to 2 to color it red
void colorPath(int *previous, int root, int goal, struct AM graph)
{
	int current = goal;												//Starting from goal
	
	if(root == goal)													//If root is the goal, no coloring required
		return;
	
	while(previous[current] != root)								//Color the edge until previous node is not root
	{
		graph.matrix[current][previous[current]] = '2';
		graph.matrix[previous[current]][current] = '2';
		current = previous[current];
	}
	graph.matrix[current][previous[current]] = '2';			//Color the last edge
	graph.matrix[previous[current]][current] = '2';	
	
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
	
	//Printing the distance
	printf("\n Distance between %d and %d is %d", root, goal, distance);
	
	//Freeing the dynamically allocated memory
	free(path);
	
	//Returning the distance
	return distance;
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
				if(graph.matrix[current][i] != '0')	//If it has an edge to ith column(node)
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
			if(graph.matrix[i][j] == '1')					//If i & j have an edge, print in the dot file (according to the color) and increase the count
			{
				fprintf(dot, "\t%d -- %d ;\n", i, j);
				count++;
			}
			else if(graph.matrix[i][j] == '2')			
			{
				fprintf(dot, "\t%d -- %d [color = red] ;\n", i, j);
				count++;
			}
		}
		if(count == 0)											//If no new edge appears, print the node itself. Important to include isolated nodes
			fprintf(dot, "\t%d ;\n", i);		
	}
	fprintf(dot, "}");										//printing the closing braces in the last line
}

//Function Definition for enqueue
//Takes a pointer to queue and integer data as input
void enqueue(struct queue *q, int data)
{
	//Initializing new node ptr
	struct node *ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->next = NULL;
	
	//Updating queue front if queue is empty, else updating next of previous rear
	if(isempty(*q) == 1)
		q->front = ptr;
	else 
		q->rear->next = ptr;
	
	//Updating rear
	q->rear = ptr;	
}

//Function Definition for dequeue
//Takes a pointer to queue
//Returns integer data
int dequeue(struct queue *q)
{
	struct node *ptr = q->front;	//Storing front in ptr
	int data = q->front->data;		//Storing data
	q->front = q->front->next;		//Updating front
	free(ptr);							//Deleting the node
	return data;						//Returning the data
}

//Function Definition to check if a queue is empty
//Takes pointer to queue
//Returns 1 if queue is empty, 0 otherwise
int isempty(struct queue q)
{
	//If front is NULL, queue is empty
	if(q.front == NULL)
		return 1;
	else return 0;
}

