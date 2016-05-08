//
//  MSTAlgorithm.cpp
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 07/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "MSTAlgorithm.h"
#include "PriorityQueue.h"

#include <cassert>
#include <vector>

const int DistanceNotRelevant = 11;

struct Pair {
    int distance;
    int prev;

    Pair(int distance) : distance(distance) {}
};

ostream& operator<<(ostream& os, const MST &mst) {
    os << "Minimal spanning tree" << endl;
    os << "Number of edges: " << mst.edges.size() << endl;
    os << "Total cost: " << mst.cost << endl;
    os << "Edges:" << endl;

    for (auto edge : mst.edges) {
        os << edge.vertexA << ' ' << edge.vertexB << endl;
    }

    return os;
}

MSTAlgorithm::MSTAlgorithm(Graph graph) : graph(graph) {
    if (graph.isConnected() == false) {
        throw "MST Algorithm cannot work on graphs which are not connected!";
    }
}

MST MSTAlgorithm::calculateMST(int source) {
    int size = graph.getV();

    vector<bool> mst(size, false);
    vector<int> minimalEdgeDistances(size, INT_MAX);
    vector<int> minimalEdges(size, -1);

    minimalEdgeDistances[source] = 0;

    for (int i = 0; i < size; ++i) {
        int v = -1;

        for (int j = 0; j < size; ++j) {
            if (!mst[j] && (v == -1 || minimalEdgeDistances[j] < minimalEdgeDistances[v])) {
                v = j;
            }
        }

        mst[v] = true;

        for (int to = 0; to < size; ++to) {
            if (mst[to]) continue;

            if (graph.getDistance(v, to) < minimalEdgeDistances[to]) {
                minimalEdgeDistances[to] = graph.getDistance(v, to);

                minimalEdges[to] = v;
            }
        }
    }

    vector<MSTEdge> resultEdges;

    int cost = 0;
    for (int i = 0; i < size; i++) {
        // TODO
        assert(minimalEdgeDistances[i] != INT_MAX);

        if (minimalEdges[i] == -1) {
            continue;
        }

        resultEdges.push_back(MSTEdge(minimalEdges[i], i));

        cost += minimalEdgeDistances[i];
    }

    MST result = MST(resultEdges, cost);

    return result;
}

void testMSTAlgorithm_trivialCase() {
    Graph graph(3);

    graph.addEdge(0, 1, DistanceNotRelevant);
    graph.addEdge(0, 2, DistanceNotRelevant);

    MSTAlgorithm algorithm(graph);

    MST mst = algorithm.calculateMST(0);

    assert(mst.cost == (DistanceNotRelevant * 2));

    assert(mst.edges[0].vertexA == 0);
    assert(mst.edges[0].vertexB == 1);

    assert(mst.edges[1].vertexA == 0);
    assert(mst.edges[1].vertexB == 2);
}

void testMSTAlgorithm_trivialCase_2() {
    Graph graph(5);

    const int SmallDistance = 1;
    const int BigDistance = 10;

    graph.addEdge(0, 1, SmallDistance);
    graph.addEdge(0, 2, SmallDistance);
    graph.addEdge(0, 3, SmallDistance);
    graph.addEdge(0, 4, SmallDistance);

    graph.addEdge(1, 2, BigDistance);
    graph.addEdge(2, 3, BigDistance);
    graph.addEdge(3, 4, BigDistance);
    graph.addEdge(1, 4, BigDistance);

    MSTAlgorithm algorithm(graph);

    MST mst = algorithm.calculateMST(0);

    assert(mst.cost == 4);
}

void testMSTAlgorithm_trivialCase_3() {
    Graph graph(3);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 15);

    MSTAlgorithm algorithm(graph);

    MST mst = algorithm.calculateMST(0);

    assert(mst.cost == 3);

    assert(mst.edges[0].vertexA == 0);
    assert(mst.edges[0].vertexB == 1);

    assert(mst.edges[1].vertexA == 0);
    assert(mst.edges[1].vertexB == 2);
}

void testMSTAlgorithm_trivialCase_4() {
    Graph graph(3);

    graph.addEdge(0, 1, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 2, 2);

    MSTAlgorithm algorithm(graph);

    MST mst = algorithm.calculateMST(0);

    assert(mst.cost == 3);

    assert(mst.edges[0].vertexA == 2);
    assert(mst.edges[0].vertexB == 1);

    assert(mst.edges[1].vertexA == 0);
    assert(mst.edges[1].vertexB == 2);
}

void testMSTAlgorithm() {
    testMSTAlgorithm_trivialCase();
    testMSTAlgorithm_trivialCase_2();
    testMSTAlgorithm_trivialCase_3();
    testMSTAlgorithm_trivialCase_4();
}
