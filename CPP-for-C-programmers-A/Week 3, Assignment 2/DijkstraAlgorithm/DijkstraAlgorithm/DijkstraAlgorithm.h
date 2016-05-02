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
