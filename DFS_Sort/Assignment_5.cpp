/*************************************************************************************************************************
Programming Assignment CS5343
Write program to do Topological sort (DFS).
your graph must have at least 10 nodes and 15 edges. It must have multiple edges going in and also coming out from some of 
the edges.
1. Run the program on a graph with no cycles.  Your print out would show all the edges of the graph.  Then it will show the 
list of vertices in the topological order.
2. Run the program on a graph that has a cycle.  Your program catches the cycle and print the list of edges that form the 
cycle.
Submit code and screen shots of the execution.

This program implements 2 directed graphs, one with a cycle and one without a cycle.  The program runs topological sort on
the graphs, outputs all the edges, and then outputs the topological order of the edges.
*************************************************************************************************************************/
#include <iostream>
#include <vector>  //included to use for adjacency list
#include <stack>   //include to hold the topological order

const int VERTICES = 11;

using namespace std;

class Graph
{
public:
	vector<vector <int>> graph;
	//constructor to initialize a graph
	Graph()
	{
		graph.resize(VERTICES);
	}
	
	//method to display edges
	void display_Edges()
	{
		int i;
		cout << "The edges of the graph are listed as: " << endl;
		for (i = 0; i < VERTICES; i++)
		{
			if (graph[i].size() != 0)
			{
				for (int j = 0; j != graph[i].size(); j++)
					cout << "(" << i << ", " << graph[i][j] << ")  ";
				cout << endl;
			}

		}
		cout << endl;
	}
	//method to add an edge
	void add_Edge(int start, int end)
	{
		graph[start].push_back(end);
	}
	
	//method to implement DFS
	void DFS(int vertex, char visited[], stack<int> &order, bool &cycle)
	{
		
		visited[vertex] = 'G';
		vector<int>::iterator i;
		for (i = graph[vertex].begin(); i != graph[vertex].end(); i++)
		{
			if (visited[*i] == 'W')
			{
				DFS(*i, visited, order, cycle);
			}
			else if (visited[*i] == 'G')
			{
				cycle = true;
				order.push(*i);
				break;
			}
		}
		//add the vertex to the stack
		order.push(vertex);
		//indicate we are through with the vertex in the visited array
		visited[vertex] = 'B';

	}

	//method that gets the cylce and outputs the vertices that make up the cycle.
	void get_cycle(stack<int> &order)
	{
		//vector to hold the order
		vector<int> cycle;
		cycle.resize(order.size());
		//fill the vector from the stack holding the order.
		for (int i = 0; i != cycle.size(); i++)
		{
			cycle[i] = order.top();
			order.pop();
		}
		//initiaize 2 counter variables to hold the location of the cycle vertices indexes
		int u = 0;
		int v = 0;
		bool check = false;
		//find the cycle vertices
		for (int i = 0; i != cycle.size(); i++)
		{
			if (check == false)
			{
				for (int j = i + 1; j != cycle.size(); j++)
				{
					if (cycle[i] == cycle[j])
					{
						u = i;
						v = j;
						check = true;
						break;
					}
				}
			}
			else
				break;
		}
		//output the cycle vertices
		while (u < v)
		{
			cout << cycle[u] << " ";
			u++;
		}
	}

	void topological()
	{
		//boolean array to determine if a vertex has been visited or not. W - node not visited, G - node visited,
		//still in use, B - node visited and finished.
		char visited[VERTICES];
		//stack to hold the topological order
		stack<int> topo;
		//boolean value to indicate if there is a cycle.
		bool cycle = false;
		//initialize array to have false in all the visited vertices
		for (int i = 0; i < VERTICES; i++)
			visited[i] = 'W';
		//run the DFS method and topo sort, for loop takes care of any unattached vertices
		for (int i = 0; i < VERTICES; i++)
		{
				if (visited[i] == 'W')
					DFS(i, visited, topo, cycle);
		};
		//if there is a cycle output the vertices that make up the cycle
		if (cycle == true)
		{
			cout << "There is a cycle from: ";
			get_cycle(topo);
		}
		else //output the topological order.
		{
			cout << "The topological order of the graph is: ";
			while (topo.empty() == false)
			{
				cout << topo.top() << " ";
				topo.pop();
			}
		}

		cout << endl << endl << endl;
	}
};


int main()
{

	cout << "This program implements two directed graphs with 10 vertices and 15 edges using an adjacency list.";
	cout << "  The program runs Topological Sort, lists the edges of the graph, and the topological sorted";
	cout << " edges.\n\n";
	
	//graph with no cycle
	Graph newGraph;
	//graph with a cycle
	Graph newGraph2;
	
	//add the edges to the first graph
	newGraph.add_Edge(0, 1);
	newGraph.add_Edge(0, 4);
	newGraph.add_Edge(1, 2);
	newGraph.add_Edge(2, 3);
	newGraph.add_Edge(2, 5);
	newGraph.add_Edge(4, 5);
	newGraph.add_Edge(5, 3);
	newGraph.add_Edge(3, 6);
	newGraph.add_Edge(2, 7);
	newGraph.add_Edge(3, 9);
	newGraph.add_Edge(6, 8);
	newGraph.add_Edge(10, 8);
	newGraph.add_Edge(1, 5);
	newGraph.add_Edge(6, 9);
	newGraph.add_Edge(4, 10);

	cout << "Graph without a cycle." << endl << endl;
	//display the edges
	newGraph.display_Edges();
	//topological sort
	newGraph.topological();

	//add the edges to the second graph
	newGraph2.add_Edge(0, 1);
	newGraph2.add_Edge(0, 4);
	newGraph2.add_Edge(1, 2);
	newGraph2.add_Edge(1, 5);
	newGraph2.add_Edge(2, 3);
	newGraph2.add_Edge(2, 7);
	newGraph2.add_Edge(3, 5);
	newGraph2.add_Edge(3, 6);
	newGraph2.add_Edge(6, 9);
	newGraph2.add_Edge(4, 6);
	newGraph2.add_Edge(4, 5);
	newGraph2.add_Edge(4, 10);
	newGraph2.add_Edge(10, 8);
	newGraph2.add_Edge(3, 9);
	newGraph2.add_Edge(8, 4);

	cout << "Graph with a cycle." << endl<< endl;
	//display the edges
	newGraph2.display_Edges();
	//topological sort
	newGraph2.topological();
	
	cout << "Graph without a cycle." << endl << endl;
	Graph newGraph3;

	newGraph3.add_Edge(0, 1);
	newGraph3.add_Edge(0, 2);
	newGraph3.add_Edge(0, 3);
	newGraph3.add_Edge(0, 6);
	newGraph3.add_Edge(6, 7);
	newGraph3.add_Edge(2, 5);
	newGraph3.add_Edge(3, 4);
	newGraph3.add_Edge(4, 5);
	newGraph3.add_Edge(3, 5);
	newGraph3.add_Edge(4, 6);
	newGraph3.add_Edge(5, 6);
	newGraph3.add_Edge(7, 8);
	newGraph3.add_Edge(1, 8);
	newGraph3.add_Edge(5, 8);
	newGraph3.add_Edge(8, 10);
	newGraph3.add_Edge(2, 9);
	newGraph3.add_Edge(9, 10);

	newGraph3.display_Edges();

	newGraph3.topological();

	cout << "Graph with a cycle." << endl << endl;

	Graph newGraph4;

	newGraph4.add_Edge(0, 1);
	newGraph4.add_Edge(0, 2);
	newGraph4.add_Edge(0, 3);
	newGraph4.add_Edge(0, 6);
	newGraph4.add_Edge(6, 7);
	newGraph4.add_Edge(2, 5);
	newGraph4.add_Edge(3, 4);
	newGraph4.add_Edge(4, 5);
	newGraph4.add_Edge(3, 5);
	newGraph4.add_Edge(4, 6);
	newGraph4.add_Edge(5, 6);
	newGraph4.add_Edge(7, 8);
	newGraph4.add_Edge(1, 8);
	newGraph4.add_Edge(5, 8);
	newGraph4.add_Edge(8, 10);
	newGraph4.add_Edge(9, 2);
	newGraph4.add_Edge(10, 9);

	newGraph4.display_Edges();

	newGraph4.topological();
	
	getchar();
	return 0;
}