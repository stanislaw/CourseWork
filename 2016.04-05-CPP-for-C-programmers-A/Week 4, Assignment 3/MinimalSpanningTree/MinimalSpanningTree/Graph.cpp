//
//  Graph.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "Graph.h"

#include <cassert>
#include <iostream>
#include <vector>

const int NoDistance = -1;

Graph::Graph(int V) {
    std::vector<std::vector<int>> matrix(
                                         V,
                                         std::vector<int>(V, NoDistance));

    this->matrix = matrix;
}

int Graph::getV() const {
    return static_cast<int>(matrix.size());
};

int Graph::getE() {
    int size = getV();

    int E2 = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) continue;

            int distance = matrix[i][j];

            if (distance != NoDistance) {
                E2 = E2 + 1;
            }
        }
    }

    int E = E2 / 2;

    return E;
};

vector<int> Graph::neighbors(int x) {
    int size = getV();

    vector<int> neighbors;

    for (int i = 0; i < size; i++) {
        if (x == i) {
            continue;
        }

        int distance = matrix[x][i];

        if (distance != NoDistance) {
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

int Graph::getDistance(int x, int y) {
    return matrix[x][y];
}

// adds to G the edge from x to y, if it is not there.
void Graph::addEdge(int x, int y, int distance) {
    if (x >= getV()) {
        throw "x vertex must be part of graph!";
    }

    if (y >= getV()) {
        throw "y vertex must be part of graph!";
    }

    this->matrix[x][y] = distance;
    this->matrix[y][x] = distance;
}

bool Graph::isConnected() {
    int size = getV();

    for (int i = 0; i < size; i++) {
        if (neighbors(i).size() == 0) {
            return false;
        }
    }

    return true;
}

// IO

ostream& operator<<(ostream& os, const Graph &graph) {
    int size = graph.getV();

    for (int i = 0; i < size; ++i) {
        os << '[' << i << ']' << " ";

        for (int j = 0; j < size; ++j) {
            os << graph.matrix[i][j] << ' ';
        }

        os << endl;
    }

    return os;
}

#pragma mark - Tests

void testGraph_Initialization_With0Vertices_getV_is0() {
    Graph graph = Graph(0);

    assert(graph.getV() == 0);
}

void testGraph_Initialization_With3Vertices_getV_is3() {
    Graph graph = Graph(3);

    assert(graph.getV() == 3);
}

void testGraph_Initialization_getE() {
    Graph graph = Graph(0);

    assert(graph.getE() == 0);
}

void testGraph_addingEdge() {
    Graph graph = Graph(3);

    int distanceNotRelevant = 27;

    graph.addEdge(0, 1, distanceNotRelevant);
    graph.addEdge(1, 2, distanceNotRelevant);
    graph.addEdge(2, 0, distanceNotRelevant);

    assert(graph.getE() == 3);
}

void testGraph_neighbors() {
    Graph graph = Graph(3);

    int distanceNotRelevant = 27;

    vector<int> neighbors = graph.neighbors(0);

    assert(neighbors.size() == 0);

    graph.addEdge(0, 1, distanceNotRelevant);
    graph.addEdge(1, 2, distanceNotRelevant);
    graph.addEdge(2, 0, distanceNotRelevant);

    neighbors = graph.neighbors(0);

    assert(neighbors.size() == 2);
    assert(neighbors == vector<int>({1, 2}));
}

void testGraph_isConnected_noEdges_should_be_false() {
    Graph graph = Graph(3);

    assert(graph.isConnected() == false);
}

void testGraph_isConnected_3edges_should_be_true() {
    Graph graph = Graph(3);

    int distanceNotRelevant = 27;

    graph.addEdge(0, 1, distanceNotRelevant);
    graph.addEdge(1, 2, distanceNotRelevant);

    assert(graph.isConnected());
}

// Test suite

void testGraph() {
    testGraph_Initialization_With0Vertices_getV_is0();
    testGraph_Initialization_With3Vertices_getV_is3();
    testGraph_Initialization_getE();
    
    testGraph_addingEdge();
    testGraph_neighbors();

    testGraph_isConnected_noEdges_should_be_false();
    testGraph_isConnected_3edges_should_be_true();
}
