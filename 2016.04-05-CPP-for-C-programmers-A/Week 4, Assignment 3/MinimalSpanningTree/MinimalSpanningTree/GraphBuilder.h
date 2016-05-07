//
//  GraphBuilder.hpp
//  MinimalSpanningTree
//
//  Created by Stanislaw Pankevich on 07/05/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef GraphBuilder_h
#define GraphBuilder_h

#include "Graph.h"

#include <string>

using namespace std;

class GraphBuilder {

private:
    string filename;
public:
    GraphBuilder(string const fileName);

    Graph build();
};

void testGraphBuilder();

#endif /* GraphBuilder_h */
