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

#include <cassert>
#include <iostream>

int main(int argc, const char * argv[]) {

    // In this homework I only implement Prim's MST algorithm.
    // I don't do Kruskal algorithm and additional extra assignment with colors because of time limits

    // PriorityQueue
    //
    // I have implemented PriorityQueue class backed by Binary Heap.
    // This class is used by MSTAlgorithm class to look up for vertexes with minimal key faster than
    // it would be with naive linear search for minimal value: we get logN instead of N.
    //
    // I have found the following two topics important for my understanding of PriorityQueue:
    // "How to implement O(logn) decrease-key operation for min-heap based Priority Queue?"
    // http://stackoverflow.com/a/31123108/598057
    // And topic linked to it:
    // "Why does Dijkstra's algorithm use decrease-key?"
    // http://stackoverflow.com/a/18540646/598057
    // It turned out that I can just use insert method without writing decrease-key method
    // as scientific paper quoted there shows.
    //
    // Gotcha about C++ templates: it turned out that I had to declare all PriorityQueue class functions in its header, not in a .cpp file - looks like it is well known limitation of CPP templates.
    // StackOverflow: Why can templates only be implemented in the header file?
    // http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file

    // GraphBuilder
    // I use separate class GraphBuilder which encapsulates the procedure of creating a graph from file.
    // I find it more natural way of making Graph class be free from IO logic (reading from file)
    // This separation allows Graph class to be free from imports of #include <fstream> and #include <iterator>
    // which are needed only for IO operations of reading from file.
    //
    // I experimented on how to read a file directly to a custom structure and it worked. For the final code I use ifstream and istream iterators. I am not sure what is proper CPP way of handling errors: what if file input is malformed?

    // MST algorithm
    //
    // I have used the following sources to understand MST algorithm:
    // http://e-maxx.ru/algo/mst_prim
    // https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9F%D1%80%D0%B8%D0%BC%D0%B0
    // http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
    //
    // The first link contains code which is broken - I have used my tests to prove that
    // it does not perform for some cases, however it inspired me in my first implementation of algorithm.

    // Tests
    testGraph();
    testPriorityQueue();
    testGraphBuilder();
    testMSTAlgorithm();

    // Homework: assignment (file TestData was taken from website)
    GraphBuilder graphBuilder("TestData.txt");

    Graph graph = graphBuilder.build();

    MSTAlgorithm algorithm(graph);

    // Here we test invariants:
    // Tree should have the same minimal cost independent
    // of vertex that we calculate MST from
    for (int i = 0; i < 20; i++) {
        MST mst = algorithm.calculateMST(i);

        assert(mst.cost == 30);
    }

    MST mst = algorithm.calculateMST(0);
    assert(mst.cost == 30);

    cout << mst << endl;

    return 0;
}
