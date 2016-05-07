//
//  GraphBuilder.cpp
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 07/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "GraphBuilder.h"

#include <cassert>
#include <fstream>
#include <iterator>
#include <iostream>

GraphBuilder::GraphBuilder(string const filename) : filename(filename) {

}

Graph GraphBuilder::build() {
    ifstream inputFile("TestData.txt");

    if (inputFile.fail()) {
        throw "File does not exist";
    }

    istream_iterator<int> iter(inputFile);
    istream_iterator<int> eof;

    int size = *(iter++);
    Graph graph = Graph(size);

    int x;
    int y;
    int distance;

    // TODO: what if file is malformed?
    while (iter != eof) {
        x = *(iter++);
        y = *(iter++);
        distance = *(iter++);

        graph.addEdge(x, y, distance);
    }

    return graph;
}

void testGraphBuilder_TestData_file() {
    GraphBuilder builder("TestData.txt");

    Graph graph = builder.build();

    assert(graph.getV() == 20);

    assert(graph.getDistance(0, 1) == 17);

    assert(graph.getDistance(1, 6) == 1);

    assert(graph.getDistance(19, 18) == 11);

    assert(graph.isConnected());
}

void testGraphBuilder() {
    testGraphBuilder_TestData_file();
}