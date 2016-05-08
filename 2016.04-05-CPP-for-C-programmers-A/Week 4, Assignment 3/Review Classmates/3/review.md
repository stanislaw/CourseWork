Hello Anton,

I have got the same result for this tree that we read from file: 30.

Here are my comments on your work:

1) Why 99999 everywhere? You could make it const int ... to avoid magic numbers in your code.

2) leng, targ <- AFAIK modern coding conventions encourage you to not cut the words. Cutting off two symbols from both variable names here doesn't save you anything but readability is decreased.

3) For MST algorithm I have created separate class MSTAlgorithm. This class is stateless: you create it with instance with Graph class and then you can call its calculateMST method multiple times with any vertex as argument. This allowed me to additionally test invariants: I have called my MST algorithm on different vertexes and ensured that the cost still was 30. Having two separate classes for MST and Graph is good separation of concerns and address Single Responsibility Principle: https://en.wikipedia.org/wiki/Single_responsibility_principle.

4) Again naming: why primaMST, why "prima", not "prim" ? What sense does it make?

5) vector < T >  pathC;    // result costs <-- this variable is not used in algorithm, it is redundant

6) I may be wrong here but this line looks very suspicious:

        for (const auto g : mstSet) {

I looked at many implementations of MST and I didn't see a single one which would include cycling through vertexes that **are already in MST**!. Your code seems to produce correct result but overall implementation looks complicated and inefficient.

7) This is probably a matter of personal preference but I find your coding style very compressed. Try looking at examples in Google or LLVM conventions - you'll see a longer variables and more indentation - let your code Breathe!

8) The following is just advice and I give it to all my classmates on this course: it is not required by assignments on this course but DO WRITE TESTS.

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

Otherwise great work, I can see the effort you have put in your work! 

Stanislav
