/*************************************************************************************************************************
Programming Assignment CS5343
1. make a graph.  you can use any representation. The graph must be 10 nodes and at least 15 edges, undirected graph
2. run Dijkstra's algorithm.
submit screen shot and the code.

This program implements an undirected graph of 10 vertices and 15 edges using an adjacency matrix to hold the weights of 
the edges.  The program then runs Djikstra's Algorithm to find the shortest paths, and prints the vertices and distances
from the source vertex.
*************************************************************************************************************************/
#include <iostream>
#include <cstdlib>	//pull the library to run the random integer generator
#include <climits>	//used to get the int_max value for integers, to use for infinity
#define NO_EDGE -1	//numerical value for no edge indicator in the adjacency matrix
#define INF INT_MAX	//numerical value for infinity for Djikstras algorithm.

using namespace std;

const int VERTICES = 10;

//the node struct is to create the priority queue for Djikstras algorithm.
struct node
{
	int vertex;			//holds the vertex of the node
	int weight;			//holds the weight to get to the vertex
	int parent_index;	//holds the parent index
	bool in_path;		//true if in the queue false if not.
};

class Graph
{
public:
	//int vertex[VERTICES];
	int adj_Matrix[VERTICES][VERTICES];

	//constructor creates an adjacency matrix with all values of NO_EDGE or -1.
	Graph()
	{
		int i, j;
		for (i = 0; i < VERTICES; i++)
		{
			//int value = rand() % 100;
			//vertex[i] = value;
			for (j = 0; j < VERTICES; j++)
			{
				adj_Matrix[i][j] = NO_EDGE;
			}
		}
	}

	//displays the adjacency matrix of the graph
	void display_Matrix()
	{
		int i, j;
		cout << endl;
		for (i = 0; i < VERTICES; i++)
		{
			cout << "	" << i << "  ";
		}
		cout << endl;
		for (i = 0; i < VERTICES; i++)
		{
			cout << i << "	";
			for (j = 0; j < VERTICES; j++)
			{
				if (adj_Matrix[i][j] == NO_EDGE)
					cout << "  " << "	";
				else
					cout << adj_Matrix[i][j] << "	";
			}
			cout << endl;
		}
		cout << endl;
	}

	//method to add an edge to the graph, undirected graph gets two edges since edge can go either way
	void add_Edge(int temp, int temp2, int weight)
	{
		adj_Matrix[temp][temp2] = weight;
		adj_Matrix[temp2][temp] = weight;
	}
	
	//heapify method used for the priority queue implemented in Djikstras algorithm
	//minimum heapify floats the minimum value to the front of the queue
	void heapify(node *arr[], int index, int size)
	{
		if (index <= size / 2)
		{
			int l = index * 2 + 1;
			int r = l + 1;
			int min = index;
			if (l < size && arr[l]->weight < arr[index]->weight)
				min = l;
			if (r < size && arr[r]->weight < arr[min]->weight)
				min = r;
			if (min != index)
			{
				node *temp = arr[index];
				arr[index] = arr[min];
				arr[min] = temp;
				heapify(arr, min, size);
			}
		}
		else
			return;
	}

	//builds the min heap for the priority queue in Djikstras algorithm
	void build_heap(node *arr[], int size)
	{
		int last_parent = size / 2;
		int i = last_parent;
		while (i > -1)
		{
			heapify(arr, i, size);
			i--;
		}
	}

	//used to swap the minimum weight in the queue with the last node in the queue
	//and shortens the queue by one each time.
	void swap(node *arr[], int heap_size)
	{
		node *temp = arr[heap_size];
		arr[heap_size] = arr[0];
		arr[0] = temp;
	}

	//method "relaxes" the weight of the edges in Djikstras algorithm
	//uses the weight of the parent vertex and recalculates the weight of the edge.
	void relax(node *arr[], int vertex, int size)
	{
		int j;
		for (j = 0; j < VERTICES; j++)
		{
			if (arr[j]->in_path==false && adj_Matrix[vertex][arr[j]->vertex] != NO_EDGE)
			{
				int e = arr[size+1]->weight + adj_Matrix[vertex][arr[j]->vertex];
				if (e < arr[j]->weight)
				{
					arr[j]->weight = e;
					arr[j]->parent_index = vertex;
				}
			}
		}
	}

	//Djikstra's algorithm, accepts the vertex to start from as the "source".  It implements a priority queue
	//in the form of a minimum heap array using the node structure.  It initializes all edges to infinity, sets the 
	//source vertex to 0 and begins running the algorith using the priority queue to get the minimum distance
	//percolated up each time.  The method then "relaxes" the edgues of the graph before running heapify on the
	//priority queue again.  The method then outputs the vertices and distances of the shortest path.
	void dijkstra(int source)
	{
		//constructs an array of nodes for the priority queue to track the vertex weight and parent vertex
		node *priority[VERTICES];
		int i = 0;
		int j = 0;
		//initialize the array setting all weights to infinity
		for (i = 0; i < VERTICES; i++)
		{
			node *newNode;
			newNode = new node;
			priority[i] = newNode;
			priority[i]->vertex = i;
			priority[i]->weight = INF;
			priority[i]->parent_index = INF;
			priority[i]->in_path = false;

		}
		//initialize the starting vertex.
		priority[source]->parent_index = NO_EDGE;
		priority[source]->weight = 0;
		//temp variables
		int min_ind;
		int heap_size = VERTICES-1;

		for (i = 0; i < VERTICES-1; i++)
		{
			//run the min heap for the priority queue
			build_heap(priority, heap_size+1);
			priority[0]->in_path = true;
			min_ind = priority[0]->vertex;
			swap(priority, heap_size);
			heap_size--;
			//relax the edges
			relax(priority, min_ind, heap_size);
			
		}
		cout << "Shortest path by Djikstra's Algorithm starting from vertex " << source << ": \n";
		for (j = VERTICES - 1; j > -1; j--)
		{
			cout << "VERTEX " << priority[j]->vertex << " PARENT " << priority[j]->parent_index << " DISTANCE " << priority[j]->weight << endl;
		}
		
	}
};

int main()
{

	cout << "This program implements an undirected graph with 10 vertices and 15 edges.  The program runs Djikstra's Algorithm ";
	cout << " to determine the shortest path and outputs the shortest path from the starting vertex.\n\n";

	Graph newGraph;

	newGraph.add_Edge(0, 1, 5);
	newGraph.add_Edge(0, 2, 3);
	newGraph.add_Edge(1, 2, 3);
	newGraph.add_Edge(1, 3, 2);
	newGraph.add_Edge(2, 3, 5);
	newGraph.add_Edge(2, 4, 2);
	newGraph.add_Edge(3, 4, 1);
	newGraph.add_Edge(3, 5, 2);
	newGraph.add_Edge(4, 6, 3);
	newGraph.add_Edge(5, 8, 4);
	newGraph.add_Edge(5, 7, 6);
	newGraph.add_Edge(6, 7, 3);
	newGraph.add_Edge(6, 8, 12);
	newGraph.add_Edge(7, 9, 15);
	newGraph.add_Edge(8, 9, 9);
	
	cout << "The adjacency matrix representation of the graph.\n\n";
	newGraph.display_Matrix();

	int start = 0;
	char again = 'Y';

	do {
		cout << "Enter an integer between 0 - 9 as the starting vertex to run Djikstra's algorith.\n";
		cin >> start;

		cout << endl;
		newGraph.dijkstra(start);
		cout << endl;

		cout << "Would you like to run the program again?  Enter Y for yes or N for no.\n";
		cin >> again;
	} while (again == 'Y' || again == 'y');

	getchar();
	return 0;
}