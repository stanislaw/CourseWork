//
//  MSTAlgorithm.cpp
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 07/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "MSTAlgorithm.h"

#include <cassert>
#include <iostream>

const int DistanceNotRelevant = 11;

MSTAlgorithm::MSTAlgorithm(Graph graph) : graph(graph) {
    if (graph.isConnected() == false) {
        throw "MST Algorithm cannot work on graphs which are not connected!";
    }
}

vector <int> MSTAlgorithm::calculateMST(int source) {


    return vector<int>();
}

void testMSTAlgorithm_trivialCase() {
    Graph graph(2);

    graph.addEdge(0, 1, DistanceNotRelevant);

    MSTAlgorithm algorithm(graph);

    assert(algorithm.calculateMST(0) == vector<int>({0, 1}));
}

void testMSTAlgorithm() {
    testMSTAlgorithm_trivialCase();
}
