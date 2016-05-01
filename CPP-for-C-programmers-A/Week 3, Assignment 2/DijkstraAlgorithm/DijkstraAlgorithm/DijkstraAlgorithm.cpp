//
//  DijkstraAlgorithm.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"

#include <cassert>
#include <iostream>
#include <queue>

DijkstraAlgorithm::DijkstraAlgorithm(Graph graph) : graph(graph) {}

class VDPairComparator{public: bool operator ()(VDPair &p1, VDPair &p2){return p1.distance > p2.distance;}};

vector <VDPair> DijkstraAlgorithm::calculateShortestPathVertices(int source, int destination) {
    int size = graph.getV();

    if (source >= size) {
        throw "source must be less than size of the graph!";
    }

    if (destination >= size) {
        throw "source must be less than size of the graph!";
    }

    vector<int> minDistances = vector<int>(size, INT_MAX);
    minDistances[source] = 0;

    priority_queue<VDPair, vector<VDPair>, VDPairComparator> queue;
    queue.push(VDPair(source, 0));

    vector<VDPair> shortestPath;

    while (!queue.empty()) {
        VDPair currentVertexPair = queue.top(); // Current vertex. The shortest distance for this has been found

        shortestPath.push_back(currentVertexPair);

        if (currentVertexPair.vertex == destination) return shortestPath;

        queue.pop();

        vector<int> neighbours = graph.neighbors(currentVertexPair.vertex);

        for (auto neighbour : neighbours) {
            int distance = graph.getDistance(currentVertexPair.vertex, neighbour);

            if (minDistances[neighbour] > (minDistances[currentVertexPair.vertex] + distance)) {
                minDistances[neighbour] = minDistances[currentVertexPair.vertex] + distance;

                queue.push(VDPair(neighbour, minDistances[neighbour]) );
            }
        }
    }

    assert(false);
    return shortestPath;
}

int DijkstraAlgorithm::calculateShortestPath(int source, int destination) {
    int shortestPath = 0;

    return shortestPath;
}

#pragma mark - Tests

void test_calculateShortestPathVertices_singleElementGraph() {
    Graph graph(1);

    DijkstraAlgorithm algorithm(graph);

    vector<VDPair> shortestPath = algorithm.calculateShortestPathVertices(0, 0);

    VDPair path = *shortestPath.begin();

    assert(path.vertex == 0);
    assert(path.distance == 0);
}

void test_calculateShortestPathVertices_threeElements() {
    Graph graph(3);

    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 22);
    graph.addEdge(0, 2, 5);

    DijkstraAlgorithm algorithm(graph);

    vector<VDPair> shortestPath = algorithm.calculateShortestPathVertices(0, 2);

    VDPair path = *shortestPath.begin();

    assert(path.vertex == 0);
    assert(path.distance == 0);

    VDPair path2 = *(shortestPath.begin() + 1);

    assert(path2.vertex == 2);
    assert(path2.distance == 5);
}

void testDijkstraAlgorithm() {
    test_calculateShortestPathVertices_singleElementGraph();
    test_calculateShortestPathVertices_threeElements();
}
