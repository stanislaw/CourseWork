// Coursera_C_to_C++_Assignment_2.cpp : Defines the entry point for the console application.
//

#include "Graph.h"
#include "Dijkstra.h"
#include <iostream>

using namespace std;

// Declare all the global constants. You can try changing these parameters to generate different graphs and shortest path calculations from different source nodes
const int numberOfNodes = 50;
const int probabilityDensityPercentage = 40;
const int minEdgeValue = 1; // Do not change this. In the graph.cpp it assumes that the min edge value is always 1
const int maxEdgaeValue = 10;

const int sourceNodeIndex = 0;

int main(int argc, char *argv[])
{
    // Declare the variables to hold the metrics like number of connected nodes and the average shortest Path cost
    int averageShortestPathCost = 0;
    int numberOfConnectedNodes = 0;
    int sumOfShortestPathCosts = 0;

    // Construct a graph with given number of Nodes, probablity density , minEdgeValue and maxEdgeValue.
    Graph* pGraph = new Graph(numberOfNodes, probabilityDensityPercentage, minEdgeValue, maxEdgaeValue);

    // Pass this graph to the Dijkstra Algorithm to compute the shortest path cost
    Dijkstra* pDijkstra = new Dijkstra(pGraph, sourceNodeIndex);

    // Print the shortest path costs to all the nodes from the source node
    cout << "Printing the shorest path costs. If the shortest path cost to any node other than source is zero then there is no connection to that node from the source" << endl;
    for (int vertex = 0; vertex < pGraph->GetNumberOfVertices(); vertex++)
    {
        // Include a node for average calculation only if a path exists between source and the given node
        if (pDijkstra->GetShortestPathCost(vertex) != 0)
        {
            sumOfShortestPathCosts += pDijkstra->GetShortestPathCost(vertex);
            numberOfConnectedNodes++;
        }
        cout << "The shorest path cost from source to vertex :" << vertex << " is " << pDijkstra->GetShortestPathCost(vertex) << endl;
    }

    if (numberOfConnectedNodes != 0)
    {
        averageShortestPathCost = sumOfShortestPathCosts / numberOfConnectedNodes;
    }

    cout << "The number of connected nodes from the source is :" << numberOfConnectedNodes << endl;
    cout << "The average Shortest path cost from source to all the connected nodes is " << averageShortestPathCost << endl;
    
    // Clean up the memory be deleting the created objects
    delete pGraph;
    delete pDijkstra;
    
    return 0;
}

