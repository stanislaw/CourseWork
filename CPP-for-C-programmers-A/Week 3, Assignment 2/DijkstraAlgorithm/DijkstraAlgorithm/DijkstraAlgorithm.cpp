//
//  DijkstraAlgorithm.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"

#include <cassert>
#include <iostream>
#include <queue>

DijkstraAlgorithm::DijkstraAlgorithm(Graph graph) : graph(graph) {}

class VDPairComparator{public: bool operator ()(VDPair &p1, VDPair &p2){return p1.distance > p2.distance;}};

VSPath DijkstraAlgorithm::calculateShortestPath(int source, int destination) {
    int size = graph.getV();

    if (source >= size) {
        throw "source must be less than size of the graph!";
    }

    if (destination >= size) {
        throw "source must be less than size of the graph!";
    }

    vector<VSPath> history = vector<VSPath>(size);

    for (int i = 0; i < size; i++) {
        history[i] = VSPath(INT_MAX);
    }
    history[source] = VSPath(0);
    history[source].story.push_back(source);

    priority_queue<VDPair, vector<VDPair>, VDPairComparator> queue;
    queue.push(VDPair(source, 0));

    vector<VDPair> shortestPath;

    while (!queue.empty()) {
        VDPair currentVertexPair = queue.top();

        shortestPath.push_back(currentVertexPair);

        if (currentVertexPair.vertex == destination) {
            return history[destination];
        }

        queue.pop();

        vector<int> neighbours = graph.neighbors(currentVertexPair.vertex);

        for (auto neighbour : neighbours) {
            int distance = graph.getDistance(currentVertexPair.vertex, neighbour);

            if (history[neighbour].distance > (history[currentVertexPair.vertex].distance + distance)) {
                history[neighbour].distance =  history[currentVertexPair.vertex].distance + distance;

                vector<int> newStory = history[currentVertexPair.vertex].story;
                newStory.push_back(neighbour);

                history[neighbour].story = newStory;

                queue.push(VDPair(neighbour, history[neighbour].distance) );
            }
        }
    }

    return VSPath(0);
}

int DijkstraAlgorithm::calculateShortestPathDistance(int source, int destination) {
    return calculateShortestPath(source, destination).distance;
}

ostream& operator<<(ostream& os, const VDPair & pair) {
    os << pair.vertex << '/' << pair.distance << endl;

    return os;
}

#pragma mark - Tests

// Test: calculateShortestPath
void test_calculateShortestPath_singleElementGraph() {
    Graph graph(1);

    DijkstraAlgorithm algorithm(graph);

    VSPath shortestPath = algorithm.calculateShortestPath(0, 0);

    assert(shortestPath.distance == 0);

    assert(shortestPath.story.size() == 1);
    assert(*shortestPath.story.begin() == 0);
}

void test_calculateShortestPathVertices_threeElements() {
    Graph graph(3);

    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 22);
    graph.addEdge(0, 2, 5);

    DijkstraAlgorithm algorithm(graph);

    VSPath shortestPath = algorithm.calculateShortestPath(0, 2);

    assert(shortestPath.distance == 5);

    assert(*shortestPath.story.begin() == 0);
    assert(*(shortestPath.story.begin() + 1) == 2);
}

void test_calculateShortestPathVertices_fiveElements() {
    Graph graph(5);

    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 4, 4);

    DijkstraAlgorithm algorithm(graph);

    VSPath shortestPath = algorithm.calculateShortestPath(0, 4);

    assert(shortestPath.distance = 10);
    assert(shortestPath.story == vector<int>({0, 1, 2, 3, 4}));
}

void test_calculateShortestPathVertices_WikipediaExample() {
    Graph graph(6);

    graph.addEdge(0, 5, 14);
    graph.addEdge(0, 2, 9);
    graph.addEdge(0, 1, 7);
    graph.addEdge(1, 2, 10);
    graph.addEdge(2, 5, 2);
    graph.addEdge(4, 5, 9);
    graph.addEdge(3, 4, 6);
    graph.addEdge(2, 3, 11);
    graph.addEdge(1, 3, 15);

    DijkstraAlgorithm algorithm(graph);

    VSPath shortestPath_0_3 = algorithm.calculateShortestPath(0, 3);

    assert(shortestPath_0_3.distance == 20);
    assert(shortestPath_0_3.story == vector<int>({0, 2, 3}));

    VSPath shortestPath_0_4 = algorithm.calculateShortestPath(0, 4);

    assert(shortestPath_0_4.distance == 20);
    assert(shortestPath_0_4.story == vector<int>({0, 2, 5, 4}));

    VSPath shortestPath_5_3 = algorithm.calculateShortestPath(5, 3);

    assert(shortestPath_5_3.distance == 13);
    assert(shortestPath_5_3.story == vector<int>({5, 2, 3}));
}

void test_calculateShortestPathVertices_threeElements_withoutEdges() {
    Graph graph(3);

    DijkstraAlgorithm algorithm(graph);

    VSPath shortestPath1 = algorithm.calculateShortestPath(0, 2);

    assert(shortestPath1.distance == 0);
    assert(shortestPath1.story == vector<int>({}));

    graph.addEdge(0, 1, 10);

    DijkstraAlgorithm algorithm2(graph);

    VSPath shortestPath2 = algorithm2.calculateShortestPath(0, 2);

    assert(shortestPath2.distance == 0);
    assert(shortestPath2.story == vector<int>({}));

    graph.addEdge(1, 2, 10);

    DijkstraAlgorithm algorithm3(graph);

    VSPath shortestPath3 = algorithm3.calculateShortestPath(0, 2);

    assert(shortestPath3.distance == 20);
    assert(shortestPath3.story == vector<int>({0, 1, 2}));
}

void test_calculateShortestPathDistance_threeElements() {
    Graph graph(3);

    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 22);
    graph.addEdge(0, 2, 5);

    DijkstraAlgorithm algorithm(graph);

    int shortestPathDistance = algorithm.calculateShortestPathDistance(0, 2);

    assert(shortestPathDistance == 5);
}

void testDijkstraAlgorithm() {
    test_calculateShortestPath_singleElementGraph();
    test_calculateShortestPathVertices_threeElements();
    test_calculateShortestPathVertices_fiveElements();
    test_calculateShortestPathVertices_WikipediaExample();

    test_calculateShortestPathVertices_threeElements_withoutEdges();

    test_calculateShortestPathDistance_threeElements();
}
