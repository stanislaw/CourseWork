//
//  main.cpp
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 06/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "Graph.h"
#include "GraphBuilder.h"
#include "PriorityQueue.h"
#include "MSTAlgorithm.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    cout << "PriorityQueue: I couldn't make it to work with templates in my previous home work. Here it is working..." << endl;
    cout << "I use separate class GraphBuilder which encapsulates the procedure of creating a graph from file..." << endl;
    cout << "I experimented on how to read a file right to my custom structure and it worked. For the final code I use ifstream and istream iterators. Not sure what is proper CPP way of handling error: what if file input is malformed?" << endl;

    testGraph();
    testPriorityQueue();
    testGraphBuilder();

    GraphBuilder graphBuilder("TestData.txt");

    Graph graph = graphBuilder.build();

    MSTAlgorithm algorithm(graph);

    return 0;
}
