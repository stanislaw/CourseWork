//
//  main.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 28/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

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
        return false;
    }

    // lists all nodes y such that there is an edge from x to y.
    vector<int> neighbors(int x) {
        vector<int> neighbors;

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

void testGraph_InitialState_Vis0_getVis0() {
    Graph graph = Graph(0);

    assert(graph.getV() == 0);
}

void testGraph_InitialState_Vis3_getVis3() {
    Graph graph = Graph(3);

    assert(graph.getV() == 3);
}

void testGraph_InitialState_getE() {
    Graph graph = Graph(0);

    assert(graph.getE() == 0);
}

void testGraph_InitialState_adjacent() {
    Graph graph = Graph(0);

    assert(graph.adjacent(0, 0) == false);
}

void testGraph_InitialState_neighbors() {
    Graph graph = Graph(0);

    assert(graph.neighbors(0).size() == 0);
}

void testGraph_addingEdge() {
    Graph graph = Graph(3);

    int distanceNotRelevant = 27;

    graph.addEdge(0, 1, distanceNotRelevant);
    graph.addEdge(1, 2, distanceNotRelevant);
    graph.addEdge(2, 0, distanceNotRelevant);

    assert(graph.getE() == 3);
}

void testSuite() {
    // Initial state
    testGraph_InitialState_Vis0_getVis0();
    testGraph_InitialState_Vis3_getVis3();
    testGraph_InitialState_getE();
    testGraph_InitialState_adjacent();
    testGraph_InitialState_neighbors();

    testGraph_addingEdge();
}

int main(int argc, const char * argv[]) {
    std::cout << "Assignment: Homework 2: Implement Dijkstra's Algorithm\n";

    testSuite();

    return 0;
}
