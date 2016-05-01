//
//  DijkstraAlgorithm.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"

#include <cassert>
#include <queue>

DijkstraAlgorithm::DijkstraAlgorithm(Graph graph) : graph(graph) {}

vector <int> DijkstraAlgorithm::calculateShortestPathVertices(int source, int destination) {
    int size = graph.getV();

    PriorityQueue<int> queue = PriorityQueue<int>(vector<int>());

    vector<int> bla;
    return bla;
}

int DijkstraAlgorithm::calculateShortestPath(int source, int destination) {
    int shortestPath = 0;

    return shortestPath;
}

#pragma mark - Tests

void testOnSingleElementGraph() {
    Graph graph(1);

    DijkstraAlgorithm algorithm(graph);

    assert(algorithm.calculateShortestPath(0, 0) == 0);
}

void testDijkstraAlgorithm() {
    testOnSingleElementGraph();
}
