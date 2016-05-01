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

    vector<int> labels;
    vector<int> vertices_source;

    for (int i = 0; i < size; i++) {
        if (i == source) {
            labels.insert(labels.begin(), 0);
        } else {
            labels.push_back(INT_MAX);
        }
    }

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
