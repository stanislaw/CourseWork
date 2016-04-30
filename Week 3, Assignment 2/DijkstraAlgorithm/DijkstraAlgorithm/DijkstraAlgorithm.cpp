//
//  DijkstraAlgorithm.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"

#include <cassert>

DijkstraAlgorithm::DijkstraAlgorithm(Graph graph) : graph(graph) {}

vector <int> DijkstraAlgorithm::calculateShortestPathVertices(int source, int destination) {
    int size = graph.getV();

    bool visited[size];
    fill_n(visited, size, false);

    vector<int> vertices;

    return vertices;
}

// *(*(w+st)+i) ==> w[st][i]
// *(*(vector+i)+j) ===> vector[i][j]

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
