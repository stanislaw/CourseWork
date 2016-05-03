
#include "graph.h"
#include <cstdlib>
#include "time.h"

// Graph constructor. takes in the params size, density min and max edge values and
// creates a random graph based on these parameters
// This constructor uses member initializer list to store the argument values into its members
Graph::Graph(int size, int density, int minEdgeValue, int maxEdgeValue):
m_size(size),
m_density(density),
m_minEdgeValue(minEdgeValue),
m_maxEdgeValue(maxEdgeValue)
{
	InitializeAdjacenyMatrix();
	CreateEdgesBasedOnDensity();	
}

Graph::~Graph()
{
}

// Returns the number of nodes/vertices present in the graph.
int Graph::GetNumberOfVertices()
{
	return m_size;
}

// This method returns the number of Edges present in the graph
int Graph::GetNumberOfEdges()
{
	int totalNumberOfEdges = 0;
	// First loop over the entire adjacency matrix to calculate the number of non zero entries
	for (int row = 0; row < m_size; row++)
	{
		for (int col = 0; col < m_size; col++)
		{
			if (m_adjacenyMatrix[row][col] != 0)
			{
				totalNumberOfEdges++;
			}
		}
	}
	// Since this is a symmetric graph, and if we count the edge from x to y as the same as node from y to x, we need to divide the total number of edges by 2
	// as each edge would have been counted twice in the prior operation
	return (totalNumberOfEdges / 2);
}

// This method adds an edge between two given nodes and assigns it a random cost
void Graph::AddEdgeBetweenNodes(int nodeX, int nodeY)
{
	m_adjacenyMatrix[nodeX][nodeY] = m_adjacenyMatrix[nodeY][nodeX] = rand() % m_maxEdgeValue + 1;
}

// This method delets an existing edge between two nodes
void Graph::DeleteEdgeBetweenNodes(int nodeX, int nodeY)
{
	m_adjacenyMatrix[nodeX][nodeY] = m_adjacenyMatrix[nodeY][nodeX] = 0;
}

// This method returns the value of the edge between two nodes
int Graph::Get_Edge_Value(int nodeX, int nodeY)
{
	return m_adjacenyMatrix[nodeX][nodeY];
}

// This method sets the cost of an edge between nodeX and nodeY to a particulat value
void Graph::Set_Edge_Value(int nodeX, int nodeY, int edge_Value)
{
	m_adjacenyMatrix[nodeX][nodeY] = edge_Value;
}

// This method returns true if there is an edge from node X to node Y else it returns false
// It bascially looks in the adjacency matrix and if index[X][Y] is non zero, it means there is a connection from X to Y
bool Graph::FIsAdjacent(int nodeX, int nodeY)
{
	if (m_adjacenyMatrix[nodeX][nodeY] != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// This method returns all the nodes that have a connection to the particular nodeX
// It basically goes through all the columns for that particlau row and collects all the columns which has a non
// zero value and then populates a vector and then returns the same
std::vector<int> Graph::GetAllNeighboursForNode(int nodeX)
{
	std::vector<int> neighbours;
	for (int col = 0; col < m_size; col++)
	{
		if (m_adjacenyMatrix[nodeX][col] != 0)
		{
			neighbours.push_back(col);
		}
	}
	return neighbours;
}

// This step creates an empty adjaceny matrix with the size specified by m_size
// This is the first step in creating the adjaceny matrix. We initially create an empty
// adjaceny matrix and then populate it based on denisty, min and max edge values
void Graph::InitializeAdjacenyMatrix()
{
	m_adjacenyMatrix.resize(m_size, std::vector<int>(m_size, 0));
}

 
// Now we popluate the adjaceny matrix, based on the density and the min and max edge values
// To assign edges based on density, we generate a random number between 1 and 100 and if that number
// is less than the probability density percentage specified (for eg 20%, 40%), then we assign an edge at that particular index
// To assign the cost of the edge we again calculate a random number between 1 and the max edge value and assign the same to that index.
// Note that since it is not a directed graph, the cost assigned from x to y is same as cost from y to x
void Graph::CreateEdgesBasedOnDensity()
{
	// Initialize the seed
	srand(time(0));
	for (int row = 0; row < m_size; row++)
	{
		for (int col = 0; col < m_size; col++)
		{
			// Leave the diagonal elements as zero values, as we do not want to have any loops in our graph
			// So only of the row is not equal to the column set the values to 1 or leave it as 0 based on probability density
			if (row != col)
			{
				// Generate a random number between 1 and 100 and compare that with the density.
				// if the number is less than density, establish a connection else dont
				int randomNumber = rand() % 100 + 1;
				if (randomNumber < m_density)
				{
					// Once we have established a connection assign the cost to the edge.
					// Generate a random number between 1 and the maxEdgeValue and assign it as the cost
					m_adjacenyMatrix[row][col] = m_adjacenyMatrix[col][row] = rand() % m_maxEdgeValue + 1;
				}
				// If the generated random number is less than the density then do not establish a connection/edge
				else
				{
					m_adjacenyMatrix[row][col] = m_adjacenyMatrix[col][row] = 0;
				}
			}
			// In this assignment we assume that there are no loops from one node to itself and hence there will be no connection from a node to itself
			else
			{
				m_adjacenyMatrix[row][col] = 0;
			}
		}
	}
}