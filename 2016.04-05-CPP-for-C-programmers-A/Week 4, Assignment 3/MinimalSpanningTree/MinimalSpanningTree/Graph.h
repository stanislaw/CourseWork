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

extern const int NoDistance;

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

    // Lists all nodes y such that there is an edge from x to y.
    // It is not used in MST algorithm because
    // I didn't find efficient way of caching neighbours
    // to not perform exhaustive enumeration over all vertexes every time
    // neighbours(...) is called
    vector<int> neighbors(int x);

    int getDistance(int x, int y);

    bool isConnected();

    friend ostream& operator<<(ostream& os, const Graph &graph);
};

void testGraph();

#endif /* Graph_h */
