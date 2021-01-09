/*
Program Name:	eulerian.c
Description	: 	Program to print an eulerian circuit if it has one
Programmer	: 	Sparsh Jain
Roll No		: 	111601026
Date			: 	October 10, 2017
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

//Structure stack to implement stack
struct stack
{
	struct node *top;
};

//Function Declarations for stack implementation
void push(struct stack *s, int data);
int pop(struct stack *s);

//Function Declarations for queue implementation
void enqueue(struct queue *q, int data);			
int dequeue(struct queue *q);
int isempty(struct queue q);
	
struct AM readAdj(FILE *adj);							//Function Declaration to read the adjecency matrix format of graph file and return the graph as structure AM
void makeDot(FILE *dot, struct AM graph);			//Function Declaration to write a dot format of the graph file from structure AM
int* BFS(struct AM graph, int root, int goal);	//Function Declaration to use Breadth First Search method to find a path between two nodes
int count(struct AM graph);							//Function Declaration to count the number of components in the graph
int check(struct AM graph, int start);				//Function Declaration to check whether a graph contains an eulerian circuit
void euler(struct AM graph, int start);			//Function Declaration to print the eulerian circuit

int main()
{
	FILE *adj;
	char adjName[31];
	int start;
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
	
	//Asking the user for starting point of the circuit
	printf("\n Enter the vertex you want to start the circuit with: ");
	scanf(" %d", &start);
	//Calling function readAdj to read the file and store it as a structured data
	graph = readAdj(adj);

	//Attempting to draw eulerian circuit only if possible
	if(check(graph, start) == 1)
		euler(graph, start);
	else if(check(graph, start) == 0)
		printf("\n An Eulerian Circuit Does Not Exist.");
	else
		printf("\n %d is an isolated vertex. Cannot draw an eulerian Circuit!", start);
	
	//Closing opened files and freeing dynamic memory
	fclose(adj);
	free(graph.matrix);
	printf("\n\n");
	return 0;
}

//Function Definition to print an eulerian circuit
//Takes structured AM graph and the starting vertex as input
//Prints the eulerian circuit
void euler(struct AM graph, int start)
{
	int i, j, current = start, *degree;
	char **matrix;
	struct stack vertices, circuit;

	vertices.top = NULL;
	circuit.top = NULL;

	matrix = (char **)calloc(graph.size, sizeof(char *));
	for(i = 0; i < graph.size; i++)
		matrix[i] = (char *)calloc(graph.size, sizeof(char));
	for(i = 0; i < graph.size; i++)
	{
		for(j = 0; j < graph.size; j++)
		{
			matrix[i][j] = graph.matrix[i][j];
		}
	}



	degree = (int *)calloc(graph.size, sizeof(int));
	for(i = 0; i < graph.size; i++)
	{
		degree[i] = 0;
		for(j = i; j < graph.size; j++)
		{
			if(matrix[i][j] != '0')	
				degree[i]++;
		}
	}

	while(degree[current] == 0 && vertices.top == NULL)
	{
		printf("\nReached Here\n");
		if(degree[current] == 0)
		{
			push(&circuit, current);
			current = pop(&vertices);
		}
		else
		{
			push(&vertices, current);
			printf("\n%d\n", current);
			for(i = 0; i < graph.size; i++)
			{
				if(matrix[current][i] != '0')
					break;
			}
			matrix[current][i] = '0';
			matrix[i][current] = '0';
			degree[current]--;
			degree[i]--;
			current = i;
		}
	}

	printf("\n %d", pop(&circuit));
	while(circuit.top != NULL)
		printf(" --> %d", pop(&circuit));
	
	for(i = 0; i < graph.size; i++)
		free(matrix[i]);
	free(matrix);
	free(degree);
}

//Function Definition to check whether a graph contains an eulerian circuit
//Takes structured AM graph and the starting vertex as input
//Returns 1 if eulerian circuit possible, 0 if not, and -1 if starting vertex is an isolated vertex
int check(struct AM graph, int start)
{
	int *degree, isolated = 0, components, i, j;

	//Storing degree of each vertex in a dynamic array
	degree = (int *)calloc(graph.size, sizeof(int));
	for(i = 0; i < graph.size; i++)
	{
		degree[i] = 0;
		for(j = 0; j < graph.size; j++)
		{
			if(graph.matrix[i][j] != '0')
				degree[i]++;
		}
		if(degree[i] == 0)
			isolated++;
		if(degree[i] % 2 == 1)	//If the degree is odd, return 0
			return 0;
	}
	
	components = count(graph);
	if(components - isolated > 1)	//If there are more than 1 components excluding the isolated vertices, return 0
		return 0;
	
	if(degree[start] == 0)			//If the starting point is an isolated vertex, return 0
		return -1;

	return 1;
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

//Function Definition to write a dot format of the graph file from structure AM
//Takes pointer to the dot file and the structured adjacency matrix as input
//Writes the dot format of the graph in the file according to the adjacency matrix
void makeDot(FILE *dot, struct AM graph)
{
	int i, j, count;
	float color;								
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
			else if(graph.matrix[i][j] == 'a')			
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

//Function Definition to push an element in stack
//Takes pointer to stack and element as input
void push(struct stack *s, int data)
{
	struct node *ptr = (struct node *)malloc(sizeof(struct node));
	ptr->data = data;
	ptr->next = s->top;
	s->top = ptr;
}

//Function Definition to pop an element from stack
//Takes pointer to stack as input
//Returns data from the deleted node
int pop(struct stack *s)
{
	struct node *ptr = s->top;
	int data = ptr->data;
	s->top = ptr->next;
	free(ptr);
	return data;
}
