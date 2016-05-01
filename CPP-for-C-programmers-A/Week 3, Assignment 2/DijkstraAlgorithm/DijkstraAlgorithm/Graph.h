//
//  Graph.h
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <vector>

using namespace std;

class Graph {

private:
    vector<vector<int> > matrix;

public:
    Graph(int V);

    int getV();
    int getE();

    void addEdge(int x, int y, int distance);
    void removeEdge(int x, int y);

    bool adjacent(int x, int y);
    vector<int> neighbors(int x);

    int getDistance(int x, int y);
};

void testGraph();

#endif /* Graph_h */
