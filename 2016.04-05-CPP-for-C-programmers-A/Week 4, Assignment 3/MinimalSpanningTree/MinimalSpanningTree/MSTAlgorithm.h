//
//  MSTAlgorithm.h
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 07/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef MSTAlgorithm_h
#define MSTAlgorithm_h

#include "Graph.h"

using namespace std;

class MSTAlgorithm {

private:
    Graph graph;

public:
    MSTAlgorithm(Graph graph);

    vector <int> calculateMST(int source);
};

void testMSTAlgorithm();

#endif /* MSTAlgorithm_h */
