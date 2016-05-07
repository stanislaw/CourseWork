//
//  main.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 28/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"
#include "Graph.h"
#include "GraphBuilder.h"
#include "PriorityQueue.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Assignment: Homework 2: Implement Dijkstra's Algorithm\n\n";

    std::cout << "I have implemented and tested four classes: Graph, PriorityQueue, DijkstraAlgorithm, GraphBuilder.\n";
    std::cout << "I used TDD approach: simple implementation based on 'assert' macros.\n";
    std::cout << "PriorityQueue is based on code found on internet. I studied it thoroughly and tested but couldn't make its template work with composite type <vertex, distance>. So I had to resort to using C++'s standard priority_queue, but still included the code of PriorityQueue.\n\n";
    std::cout << "I have learned: \n";
    std::cout << "- How to use vector\n";
    std::cout << "- How to declare classes in .h/.cpp files\n";
    std::cout << "- In contrast to Objective-C I can declare classes on stack. Interesting gotcha is that I cannot use forward declarations in this project because I built everything as stack-allocated (no pointers!)\n";

    std::cout << "\n";
    std::cout << "Everything seems to be working however I am pretty sure that my implementation of Dijkstra algorithm is not efficient as it should be, the coding conventions are still not clear\n\n";

    std::cout << "TODO: make Dijkstra Algorithm work with my PriorityQueue - make it work with composite types.\n\n";
    std::cout << "Below are the results of simulation on Graph with 50 vertexes and 20% and 40% densities:\n";
    std::cout << "\n";

    testGraph();
    testPriorityQueue();
    testDijkstraAlgorithm();
    testGraphBuilder();

    const int size = 50;

    // 50 vertexes, 20% density
    GraphBuilder builder_50_20(size, 0.2, 1, 9);
    Graph graph_50_20 = builder_50_20.build();

    int shortestPathSum_50_20 = 0;

    for (int i = 1; i < size; i++) {
        DijkstraAlgorithm algorithm_50_20(graph_50_20);
        VSPath shortestPath = algorithm_50_20.calculateShortestPath(0, i);

        shortestPathSum_50_20 += shortestPath.distance;
    }

    float average_percents_50_20 = static_cast<float>(shortestPathSum_50_20) / (size - 1);

    cout << "Average path length for Graph with 50 vertexes and 20% density is: " << average_percents_50_20 << endl;

    // 50 vertexes, 40% density
    GraphBuilder builder_50_40(size, 0.4, 1, 9);
    Graph graph_50_40 = builder_50_40.build();
    
    int shortestPathSum_50_40 = 0;

    for (int i = 1; i < size; i++) {
        DijkstraAlgorithm algorithm_50_40(graph_50_40);
        VSPath shortestPath = algorithm_50_40.calculateShortestPath(0, i);

        shortestPathSum_50_40 += shortestPath.distance;
    }

    float average_percents_50_40 = static_cast<float>(shortestPathSum_50_40) / (size - 1);

    cout << "Average path length for Graph with 50 vertexes and 40% density is: " << average_percents_50_40 << endl;

    return 0;
}
