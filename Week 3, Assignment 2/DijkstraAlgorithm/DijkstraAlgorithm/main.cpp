//
//  main.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 28/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "DijkstraAlgorithm.h"
#include "Graph.h"
#include "PriorityQueue.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Assignment: Homework 2: Implement Dijkstra's Algorithm\n";

    testGraph();
    testPriorityQueue();
    testDijkstraAlgorithm();

    return 0;
}
