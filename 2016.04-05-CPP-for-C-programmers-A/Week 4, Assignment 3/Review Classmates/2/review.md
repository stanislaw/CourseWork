Hello Nakarin,

Your implementation is quite similar to mine in terms of both code and result. I have got the same result for this tree that we read from file: 30.

I am giving you 10 grade since everything looks good (especially your laconic coding style is noticeable). The following are just my minor remarks on your implementation:

1) In my implementation I made my algorithm to work from arbitrary vertexes, not only from 0.

2) My MSTAlgorithm class is stateless: you create it with instance with Graph class and then you can call calculateMST multiple times with any vertex as argument (comment 1). I think it is better factoring of responsibilities between constructor of algorithm and its calculateMST method since actual machinery of MST algorithm happens in calculateMST, not in algorithm class's constructor.

3) int** cost; <--- why not use two-dimensional vector? Again in my opinion it is more CPP-ish style of working with arrays.

4) bool file_available; is not used but that's fine ;)

5) The following is just advice and I give it to all my classmates on this course: it is not required by assignments on this course but DO WRITE TESTS.

I use TDD approach to implement my homework tasks: tests are great additional way of proving that your code actually works. Here is example of test from my homework:

#include "Graph.h"

#include <cassert>

void test_calculateShortestPathDistance_threeElements() {
    Graph graph(3);

    graph.addEdge(0, 1, 11);
    graph.addEdge(1, 2, 22);
    graph.addEdge(0, 2, 5);

    DijkstraAlgorithm algorithm(graph);

    int shortestPathDistance = algorithm.calculateShortestPathDistance(0, 2);

    assert(shortestPathDistance == 5);
}

If shortestPathDistance is not 5 this test will fail clearly showing you the source line. For this homework I have around 20-30 tests: Graph, PriorityQueue, MSTAlgorithm, GraphBuilder - all these classes are covered with basic tests.

I highly encourage you to adopt this approach.

For your interest here is my assignment on Github:

https://github.com/stanislaw/Coursera/tree/294a869330f8621073f8634782472ecce13e3a97/2016.04-05-CPP-for-C-programmers-A/Week%204%2C%20Assignment%203/MinimalSpanningTree/MinimalSpanningTree

Great work! 

Stanislav
