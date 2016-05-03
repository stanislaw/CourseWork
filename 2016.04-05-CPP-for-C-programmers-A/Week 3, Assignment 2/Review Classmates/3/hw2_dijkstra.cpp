#include <iostream>
#include <queue>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// not used, but for default value
const int DEFAULT_VERTICES_NODE = 50;

class Graph {
private:
	// vertex node
	int m_V;

	// adjacency matrix
	double** m_graph;

	double density;
	double minWeight;
	double maxWeight;

public:
	// constructor
	Graph(int V, double density, double minWeight, double maxWeight);
	// destructor
	~Graph();

	double** getGraph2DArray()
	{
		return m_graph;
	}

	int get_V_number()
	{
		return m_V;
	}
};

//generate a random double nubmer between fMin and fMax
inline double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

// generate probabilty between 0 and 1
inline double prob()
{
	return (double)rand() / RAND_MAX ;
}

//generate a random graph size*size and the edge density and range are assigned
Graph::Graph(int size, double density, double minWeight, double maxWeight)
{
	// initialize
	m_V = size;

	srand(time(0)); // seed rand()

	m_graph = new double*[size];

	for(int i = 0; i < size; ++i)
	{
		m_graph[i] = new double[size];
	}

	for(int i = 0; i < size; i++)
	{
		for(int j = i; j < size; j++)
		{
			if(i == j)
			{
				m_graph[i][j] = 0; //no loops
			}
			else
			{
				// symmetric matrix means undirected graph
				m_graph[i][j] = m_graph[j][i] = (prob() < density) ? fRand(minWeight, maxWeight) : numeric_limits<double>::max();
			}
		}
	}
}

Graph::~Graph()
{
	//destructor for ShortestPath
	for(int i = 0; i < m_V; i++)
	{
		delete [] m_graph[i];
	}
	delete [] m_graph;
}


class ShortestPath {
private:
	Graph *m_graph;
	int m_Vertex_Count;
	double **m_graph_2D_array;

	// adjacency matrix, each weight on edge
	double **weight;

	double *dist;
	int *previous;
	bool *closeSet;

public:
	ShortestPath(Graph *graph, int source);
	~ShortestPath();

	// return the average path length
	double average_length();
};

// struct for the adjacent node will be put into Priority Queue
struct Node
{
	// v is node, d is the distance
	int v;
	double dist;
};

bool operator< (const Node& n1, const Node& n2)
{
	return n1.dist > n2.dist;
}

ShortestPath::ShortestPath(Graph *graph, int source)
{
	// Initialization
	m_graph = graph;

	// get vertices node from graph object
	m_Vertex_Count = m_graph->get_V_number();

	// init weight matrix
	weight = new double*[m_Vertex_Count];
	for(int i = 0; i < m_Vertex_Count; ++i)
	{
		weight[i] = new double[m_Vertex_Count];
	}

	// init array used in dijkstra's algorithm
	dist = new double[m_Vertex_Count];
	previous = new int[m_Vertex_Count];
	closeSet = new bool[m_Vertex_Count];

	// weight matrix is the same as **m_graph of graph object
	m_graph_2D_array = m_graph->getGraph2DArray();

	// assign 2D array element to weight matrix
	for(int i = 0; i < m_Vertex_Count; i++)
	{
		for(int j = 0; j < m_Vertex_Count; j++)
		{
			weight[i][j] = m_graph_2D_array[i][j];
		}
	}

	// init close set, in beginning, no vertex node in it
	for (int i = 0; i < m_Vertex_Count; i++)
	{
		closeSet[i] = false;
	}

	// dist[i] means distance from source node[0] to node [i]
	// set all node are unreachable.
	for (int i = 0; i < m_Vertex_Count; i++)
	{
		// itit dist of all node to MAX number( mean infinite), not reachable now
		dist[i] = numeric_limits<double>::max();
	}


	// C++ STL Priority Queue
	priority_queue<Node> PQ;

	dist[source] = 0;
	previous[source] = source;

	PQ.push( (Node){source, dist[source]} );

	for (int i = 0; i < m_Vertex_Count; i++)
	{
		// find out the next node contains the least cost
		int u = -1;

		// Remove and return best vertex node to the closeSet
		while ( !PQ.empty() &&
				closeSet[u = PQ.top().v] )
		{
			PQ.pop();
		}

		if (u == -1)
		{
			break;
		}

		closeSet[u] = true;

		// for each neighbor v of u:
		for (int v = 0; v < m_Vertex_Count; v++)
		{
			// only v that is still in Q
			if ( !closeSet[v] && dist[u] + weight[u][v] < dist[v] )
			{
				dist[v] = dist[u] + weight[u][v];
				previous[v] = u;

				// Let Priority Queue to process the next most appropriate node
				PQ.push( (Node){v, dist[v]} );
			}
		}
	}
}

ShortestPath::~ShortestPath()
{
	//destructor for ShortestPath
	for(int i = 0; i < m_Vertex_Count; i++)
	{
		delete [] weight[i];
	}
	delete [] weight;

	delete [] dist;
	delete [] previous;
	delete [] closeSet;
}

double ShortestPath::average_length()
{
	double sum_path_dist = 0;
	/* To get an average path length, compute the 49 paths:
	*  1 to 2, 1 to 3, 1 to 4, …, 1 to 50. */

	// compute the other 49 path (vertex node - 1)
	int total_valid_count = m_Vertex_Count-1;

	// notice index from 1, not 0, because dist[source] is 0
	for(int i = 1; i < m_Vertex_Count; i++)
	{
		// sum of the total path length
		if(dist[i] != numeric_limits<double>::max())
		{
			sum_path_dist += dist[i];
		}
		//discard the non reachable node
		else
		{
			// if the dist[i] remain INF, it means non reachable, ignore this item
			total_valid_count--;
		}
	}

	return sum_path_dist / total_valid_count;
}

int main()
{
/*
 * Printout of program, 200 words on what you learned, and output showing the average path length calculation.
 * Use densities: 20% and 40% on a graph of 50 nodes with a distance range of 1.0 to 10.0.
 * To get an average path length, compute the 49 paths: 1 to 2, 1 to 3, 1 to 4, …, 1 to 50.
 */
	cout << endl;
	cout << "I learned the techiques of creating a class, and inistance of it from this course" << endl << endl;
	cout << "I used the skill of the lecture on the course to generate the random graph that teacher told." << endl << endl;;
	cout << "And I used the C++ STL priority queue for my tool to pop the approiate candidate" << endl;
	cout << "to implement Dijkstra's shortest path algorithm." << endl << endl;
	cout << "I used the pointer of the graph object to ShortestPath object," << endl;
	cout << "and indicate the source node index is 0 on main function. " << endl << endl;
	cout << "I don't implement all the member function of the potiental interface for all class" << endl;
	cout << "Because of the calculation of the average path length," << endl;
	cout << "it just needs a few major factor, variables, and functions." << endl << endl;
	cout << "So I think these member functions are enough." << endl;

	cout << endl;
	cout << "Generate a graph of 50 nodes with a distance range of 1.0 to 10.0 with different density below." << endl;
	cout << "Find out the Dijkstra's shortest path distance: " << endl;
	cout << endl;

	cout << "Density is 20 %" << endl;


	// Graph(int size, double density, double minWeight, double maxWeight)
	Graph *graph_20percent = new Graph(50, 0.2, 1.0, 10.0);

	// ShortestPath(Graph *graph, int source);
	ShortestPath *shortestPath_20percent = new ShortestPath(graph_20percent, 0);

	cout << "The average path length is " << shortestPath_20percent->average_length() << endl << endl;


	cout << "Density is 40 %" << endl;

	Graph *graph_40percent = new Graph(50, 0.4, 1.0, 10.0);

	ShortestPath *shortestPath_40percent = new ShortestPath(graph_40percent, 0);

	cout << "The average path length is " << shortestPath_40percent->average_length() << endl << endl;

	return 0;
}
