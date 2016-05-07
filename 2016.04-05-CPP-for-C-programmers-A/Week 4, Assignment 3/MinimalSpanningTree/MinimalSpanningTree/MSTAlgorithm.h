//
//  MSTAlgorithm.h
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 07/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef MSTAlgorithm_h
#define MSTAlgorithm_h

#include "Graph.h"

#include <iostream>

using namespace std;

struct MSTEdge {
    int vertexA;
    int vertexB;

    MSTEdge() : vertexA(-1), vertexB(-1) {}
    MSTEdge(int vertexA, int vertexB) : vertexA(vertexA), vertexB(vertexB) {}
};

struct MST {
    vector<MSTEdge> edges;
    int cost;

    MST(vector<MSTEdge> edges, int cost) : edges(edges), cost(cost) {}
};

ostream& operator<<(ostream& os, const MST &mst);

class MSTAlgorithm {

private:
    Graph graph;

public:
    MSTAlgorithm(Graph graph);

    MST calculateMST(int source);
};

void testMSTAlgorithm();

#endif /* MSTAlgorithm_h */
