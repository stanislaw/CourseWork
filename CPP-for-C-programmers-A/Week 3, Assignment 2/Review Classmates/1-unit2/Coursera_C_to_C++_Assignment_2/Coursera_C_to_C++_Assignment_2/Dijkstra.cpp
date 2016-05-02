
#include "Dijkstra.h"
#include "Graph.h"

// The constructor of the Dijkstra object.
// It takes in a graph and the desired source node from which the shortest paths needs to be calculated
// Initilization of some of the members is done through a member initialization list
// Members that require special initilization are handled separately
Dijkstra::Dijkstra(Graph* pGraph, int source):
m_pGraph(pGraph),
m_source(source)
{
	// Perform all the other initilizations and computations only if the passed in graph is not null
	if (m_pGraph != nullptr)
	{
		m_numberOfVertices = m_pGraph->GetNumberOfVertices();
		InitializeShortestPathFoundVector();
		InitializeShortestPathCostVector();
		ComputShortestPathFromSourceToAllNodes();		
	}
}

Dijkstra::~Dijkstra()
{
}

// Initialize the shortestPathFound Vector. Initially all values are false
void Dijkstra::InitializeShortestPathFoundVector()
{	
	// Initialize the vector of shortestpathFound for all the vertices of the graph to false
	for (int i = 0; i < m_numberOfVertices; i++)
	{
		m_shortestPathFound.push_back(false);
	}

}

// Initialize the ShortestPathCostVector. Initially all of them are set to Infinity(INT_MAX)
void Dijkstra::InitializeShortestPathCostVector()
{	
	// Initailize the shortestPathCost for all the vertices of the graph to INT_MAX (As per the algorithm this is equivalent to initializing it to infinity)	
	for (int i = 0; i < m_numberOfVertices; i++)
	{
		m_shortestPathCost.push_back(INT_MAX);
	}
}


// This method returns the shortest path cost from source to any given destination.
// If no path is found from source to destination it returns zero
int Dijkstra::GetShortestPathCost(int destination)
{
	if (m_shortestPathCost[destination] != INT_MAX)
	{
		return m_shortestPathCost[destination];
	}
	else
	{
		return 0;
	}
	
}

// This is the method that implements the meat of the Dijkstra's algorithm.
// At the end of this method, the shortestPathFound and the shortestPathCost vectors are populated with theier respective vavlues based on computation
void Dijkstra::ComputShortestPathFromSourceToAllNodes()
{
	// Since we have a graph which is not directed and has no loops, the cost from source to source is zero
	m_shortestPathCost[m_source] = 0;

	// Now we write the loop to find the minimum distance from the source to all the vertices
	for (int vertex = 0; vertex < m_numberOfVertices; vertex++)
	{
		// Go over all the vertices that have not yet been processed. Pick the vertex which has the minimum distance.
		// When this method is executed the first time, it will always end up being the soucre as only the source has the cost set
		// and it is the only valid vertex in the m_shortestPathCost which has a valid value

		int minDistanceVertex = CalcualteMinimumDistanceVertex();

		// Now once we have found the minumum distance vertex, add it to the processed set or the closed set
		m_shortestPathFound[minDistanceVertex] = true;

		// Now for the newly found minimum distance vertex update the cost to its neighbours
		// the outer for loop already uses the loop indexer as vertex and hence I am using a similar but a different identifier here as node
		for (int node = 0; node < m_numberOfVertices; node++)
		{
			// We now update the m_shortestPathCost, but it is done only if the following conditions are satisfied
			// The shortest path is not yet found for this node
			if (m_shortestPathFound[node] == false)
			{
				// There is a connection/ edge present in the graph from the minDistanceVertex to this node
				if (m_pGraph->FIsAdjacent(minDistanceVertex, node))
				{
					// The distance from source to this node through minDistanceVertex is less than the earlier distances from source to this node
					if (m_shortestPathCost[minDistanceVertex] != INT_MAX &&
						(m_shortestPathCost[minDistanceVertex] + m_pGraph->Get_Edge_Value(minDistanceVertex, node)) < m_shortestPathCost[node])
					{
						m_shortestPathCost[node] = m_shortestPathCost[minDistanceVertex] + m_pGraph->Get_Edge_Value(minDistanceVertex, node);
					}
				}
			}
		}
	}
}

// This method is used to calculate the minumum distance vertex from any given node/vertex.
// The minimum distance vertex is the one for which a connection exists and the cost of the connection is the least
int Dijkstra::CalcualteMinimumDistanceVertex()
{
	int minDistance = INT_MAX;
	int min_vertex;

	for (int vertex = 0; vertex < m_numberOfVertices; vertex++)
	{
		if (m_shortestPathFound[vertex] == false)
		{
			if (m_shortestPathCost[vertex] <= minDistance)
			{
				minDistance = m_shortestPathCost[vertex];
				min_vertex = vertex;
			}
		}
	}

	return min_vertex;
}

