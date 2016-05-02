//
//  GraphBuilder.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 02/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "GraphBuilder.h"

#include <cassert>
#include <iostream>
#include <random>

GraphBuilder::GraphBuilder(int V, float density, int minDistance, int maxDistance) :
    V(V), minDistance(minDistance), maxDistance(maxDistance) {

    assert(density >= 0);
    assert(density <= 1);

    this->density = density;
}

Graph GraphBuilder::build() {
    Graph graph(V);

    int size = graph.getV();

    srand(clock());

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {

            // http://stackoverflow.com/a/7560564/598057
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_int_distribution<> distr(0, 100);

            float random = static_cast<float>(distr(eng)) / 100;

            if (random <= density) {
                std::uniform_int_distribution<> distance_distr(minDistance, maxDistance);

                graph.addEdge(i, j, distance_distr(eng));
            }
        }
    }

    return graph;
}

void test_build_createsGraph() {
    int V = 5;
    int E = (V * V - V) / 2;

    for (int i = 0; i < 1000; i++) {
        GraphBuilder builder(V, 1, 1, 1);

        Graph graph = builder.build();

        assert(graph.getV() == 5);

        if (graph.getE() != E) {
            cout << "wrong: " << graph.getE() << ' ' << E << endl;
            assert(graph.getE() == E);
        }
    }
}

void testGraphBuilder() {
    test_build_createsGraph();
}
