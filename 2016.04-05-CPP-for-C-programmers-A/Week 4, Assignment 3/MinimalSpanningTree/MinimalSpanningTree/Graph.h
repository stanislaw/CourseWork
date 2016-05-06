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

    int getV() const;

    int getE();

    void addEdge(int x, int y, int distance);

    bool adjacent(int x, int y);

    // lists all nodes y such that there is an edge from x to y.
    vector<int> neighbors(int x);

    int getDistance(int x, int y);

    bool isConnected();

    friend ostream& operator<<(ostream& os, const Graph &graph);
};

void testGraph();

#endif /* Graph_h */
