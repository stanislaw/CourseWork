#include <vector>

using namespace std;
// Forward declaration of the class Graph
class Graph;


// This class is the one which implements Dijkstra Shortest path algorithm.
// This class takes in as its constructor parameters a graph and the source from which we would like to calculate the shortest path. The class computes the shortest paths to all the
// nodes/vertices in the graph and stores the same in a vector. The public API has a method which returns the cost from the source to any given node of the graph. If there exists no connection
// or possible paths from source to destination then it returns zero.
class Dijkstra
{
public:
	Dijkstra(Graph* pGraph, int source);
	~Dijkstra();	
	int GetShortestPathCost(int destination);

private:
	Graph*				m_pGraph;			// Store the graph as a member variable
	int					m_source;			// Store the source node
	int					m_numberOfVertices;	// Member varibale which keeps track of the number of vertices of the graph
	std::vector<int>	m_shortestPathCost;	// A vector of booleans which indicate if a shortest path has been found between source and all the nodes/vertices of the graph
	std::vector<bool>	m_shortestPathFound;// A vector of the cost of the shortest path between the source node and all the nodes of the graph

	void InitializeShortestPathFoundVector();
	void InitializeShortestPathCostVector();
	void ComputShortestPathFromSourceToAllNodes();
	int CalcualteMinimumDistanceVertex();
};