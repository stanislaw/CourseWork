//
//  DijkstraAlgorithm.h
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef DijkstraAlgorithm_h
#define DijkstraAlgorithm_h

#include "Graph.h"
#include "PriorityQueue.h"

#include <vector>

using namespace std;

struct VDPair {
    int vertex;
    int distance;

    VDPair(int vertex, int distance) : vertex(vertex), distance(distance) {}

    friend ostream& operator<<(ostream& os, const VDPair & dt);
};

struct VSPath {
    int distance;
    vector<int> path;

    VSPath(int distance = 0) : distance(distance), path() {}

    friend ostream& operator<<(ostream& os, const VSPath &path);
};

// Based on russian Wikipedia page for Dijkstra's algorithm:
// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%94%D0%B5%D0%B9%D0%BA%D1%81%D1%82%D1%80%D1%8B
// and Quora's examples of implementation:
// https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm

class DijkstraAlgorithm {

private:
    Graph graph;

public:
    DijkstraAlgorithm(Graph graph);

    VSPath calculateShortestPath(int source, int destination);
    int calculateShortestPathDistance(int source, int destination);
};


void testDijkstraAlgorithm();

#endif /* DijkstraAlgorithm_h */
