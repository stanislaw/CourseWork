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
};

class DijkstraAlgorithm {

private:
    Graph graph;

public:
    DijkstraAlgorithm(Graph graph);

    vector <VDPair> calculateShortestPathVertices(int source, int destination);
    int calculateShortestPath(int source, int destination);
};


void testDijkstraAlgorithm();

#endif /* DijkstraAlgorithm_h */
