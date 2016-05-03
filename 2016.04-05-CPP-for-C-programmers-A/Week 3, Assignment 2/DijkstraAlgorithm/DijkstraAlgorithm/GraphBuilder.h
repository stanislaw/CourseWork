//
//  GraphBuilder.h
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 02/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef GraphBuilder_h
#define GraphBuilder_h

#include "Graph.h"

class GraphBuilder {

private:
    int V;
    float density;
    int minDistance;
    int maxDistance;

public:
    GraphBuilder(int V, float density, int minDistance, int maxDistance);

    Graph build();
};

void testGraphBuilder();

#endif /* GraphBuilder_h */
