#include <vector>

using namespace std;
// This class is an implementation of an undirected graph using an array/matrix representation
// A graph is essentailly represented by a two dimensional array of [size][size] where the value 
// at any index [x][y] is the cost associated with the graph and if the value is 0 it means that there is no edge
// between x and y. It is an undirected graph and hence the cost from x to y is same as the cost from y to x
// which will result in a symetric matrix along the diagonal. Now as far as the diagonal is concerned, there are no loops
// and hence the cost to go from x to x is always 0. So now to re define connected edges. An index not along the diagonal
// having a non zero value means that there is a connection between those two nodes and the value represents the cost. If 
// any index has a zero value and is not along the diagonal then there is no connection between those two nodes

// I have implemented many of the public API's as prescribed in the assignment tips. Note that however not all of the public method here, tough implemented are used in the context
// of this assignemnt. It is just to server as an extensibile features for representing Graph as a data structure

class Graph
{
public:
	Graph(int size, int density, int minEdgeValue, int maxEdgeValue);
	~Graph();

	int GetNumberOfVertices();
	int GetNumberOfEdges();
	bool FIsAdjacent(int nodeX, int nodeY);
	std::vector<int> GetAllNeighboursForNode(int nodeX);
	void AddEdgeBetweenNodes(int nodeX, int nodeY);
	void DeleteEdgeBetweenNodes(int nodeX, int nodeY);	
	int Get_Edge_Value(int nodeX, int nodeY);
	void Set_Edge_Value(int nodeX, int nodeY, int edge_Value);

private:
	int								m_size;				// This represents the number of nodes/vertices in the graph
	int								m_density;			// This represents the density of the graph
	int								m_minEdgeValue;		// This represents the minimum cost if an edge exists between two nodes
	int								m_maxEdgeValue;		// This represents the maximum cost of the edge between two nodes
	std::vector<std::vector <int> > m_adjacenyMatrix;	// This represents the adjaceny Matrix

	void InitializeAdjacenyMatrix();
	void CreateEdgesBasedOnDensity();		
};