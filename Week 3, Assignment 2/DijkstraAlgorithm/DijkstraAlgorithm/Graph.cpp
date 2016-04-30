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

using namespace std;

const int NoDistance = 0;

class Graph {

private:
    vector<vector<int>> matrix;

public:
    Graph(int V) {
        // TODO: write test for default value 0
        std::vector<std::vector<int>> matrix(
                                             V,
                                             std::vector<int>(V, NoDistance));

        this->matrix = matrix;
    }

    // returns the number of vertices in the graph
    int getV() {
        return static_cast<int>(matrix.size());
    };

    // returns the number of edges in the graph
    int getE() {
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

    // tests whether there is an edge from node x to node y.
    bool adjacent(int x, int y) {
        return matrix[x][y] != NoDistance;
    }

    // lists all nodes y such that there is an edge from x to y.
    vector<int> neighbors(int x) {
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

    // adds to G the edge from x to y, if it is not there.
    void addEdge(int x, int y, int distance) {
        this->matrix[x][y] = distance;
        this->matrix[y][x] = distance;
    }

    // removes the edge from x to y, if it is there.
    void removeEdge(int x, int y) {
        //
    }
};

// Initialization

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

//

void testGraph_addingEdge() {
    Graph graph = Graph(3);

    int distanceNotRelevant = 27;

    graph.addEdge(0, 1, distanceNotRelevant);
    graph.addEdge(1, 2, distanceNotRelevant);
    graph.addEdge(2, 0, distanceNotRelevant);

    assert(graph.getE() == 3);
}

void testGraph_adjacent() {
    Graph graph = Graph(3);

    int distanceNotRelevant = 27;

    assert(graph.adjacent(0, 1) == false);
    assert(graph.adjacent(1, 2) == false);
    assert(graph.adjacent(2, 0) == false);

    graph.addEdge(0, 1, distanceNotRelevant);
    graph.addEdge(1, 2, distanceNotRelevant);
    graph.addEdge(2, 0, distanceNotRelevant);

    assert(graph.adjacent(0, 1));
    assert(graph.adjacent(1, 2));
    assert(graph.adjacent(2, 0));
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
}

// Test suite

void testGraph() {
    // Initial state
    testGraph_Initialization_With0Vertices_getV_is0();
    testGraph_Initialization_With3Vertices_getV_is3();
    testGraph_Initialization_getE();
    
    // ...
    testGraph_addingEdge();
    testGraph_adjacent();
    testGraph_neighbors();
}
