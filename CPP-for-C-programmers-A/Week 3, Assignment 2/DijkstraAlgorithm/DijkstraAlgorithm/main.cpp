//
//  main.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 28/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"
#include "Graph.h"
#include "GraphBuilder.h"
#include "PriorityQueue.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Assignment: Homework 2: Implement Dijkstra's Algorithm\n";

    testGraph();
    testPriorityQueue();
    testDijkstraAlgorithm();
    testGraphBuilder();

    GraphBuilder builder(50, 0.2, 1, 9);

    Graph graph = builder.build();

    cout << graph;

    DijkstraAlgorithm algorithm(graph);

    VSPath shortestPath = algorithm.calculateShortestPath(0, 49);

    cout << shortestPath;

    return 0;
}
