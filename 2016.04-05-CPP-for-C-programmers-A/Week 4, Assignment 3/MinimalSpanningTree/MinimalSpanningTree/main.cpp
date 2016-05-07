//
//  main.cpp
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 06/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "Graph.h"
#include "PriorityQueue.h"

#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

struct Tripple {
    int a;
    int b;
    int c;
};

int main(int argc, const char * argv[]) {
    cout << "PriorityQueue: I couldn't make it to work with templates in my previous home work. Here it is working..." << endl;

    testGraph();
    testPriorityQueue();

    // assert(graph.isConnected());

    ifstream inputFile("TestData.txt");
    if (inputFile.fail()) {
        throw "File does not exist";
    }

    istream_iterator<int> begin(inputFile);
    istream_iterator<int> end;

    for(istream_iterator<int> it = begin; it != end; ++it) {
        cout << (*it) << "@@\n";
    }

    return 0;
}
