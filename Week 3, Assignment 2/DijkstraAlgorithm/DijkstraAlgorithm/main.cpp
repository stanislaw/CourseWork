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

class Graph {

private:
    vector<vector<int>> matrix;

public:
    Graph(int V) {
        std::vector<std::vector<int>> matrix(
                                          V,
                                          std::vector<int>(V));

        this->matrix = matrix;
    }

    // returns the number of vertices in the graph
    int getV() {
        return static_cast<int>(matrix.size());
    };

    // returns the number of edges in the graph
    int getE() {
        return 0;
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
    void addEdge(int x, int y) {
        // ...
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

void testGraph_InitialState_Vis1_getVis1() {
    Graph graph = Graph(1);

    assert(graph.getV() == 1);
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

// ...

//void testGraph_addingEdge() {
//    Graph graph = Graph(0);
//
//    graph.addEdge(0, 1);
//
//    assert(graph.getE() == 1);
//}

void testSuite() {
    // Initial state
    testGraph_InitialState_Vis0_getVis0();
    testGraph_InitialState_Vis1_getVis1();
    testGraph_InitialState_getE();
    testGraph_InitialState_adjacent();
    testGraph_InitialState_neighbors();

    // ...
    // testGraph_addingEdge();
}

int main(int argc, const char * argv[]) {
    std::cout << "Assignment: Homework 2: Implement Dijkstra's Algorithm\n";

    testSuite();

    return 0;
}
