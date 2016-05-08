Hello Ni,

I have got the same result for this tree that we read from file: 30. I am not Dijkstra so I am not able to prove that your code works 100% correctly just by looking at it (the same goes about code) but at least we got the same result :)

Here are my comments on your implementation:

1) Line 384: vector<int> minmumSpanningTree = myMST.Path(initialNodeIndex);

Why didn't you make your code **reentrant** ? What if I decide to call this method twice like myMST.Path(initialNodeIndex) and then myMST.Path(3)? The way your code is written the algorithm will not be run and you'll return the same result as you return for the first invocation of Path with initialNodeIndex. I think that generic implementation of algorithm should be stateless: you create your algorithm with some graph and then you can invoke calculate MST as many time as you want starting from different vertexes.

Instead of storing the result of your calculation in mCloseSet variable, you could just create custom struct like 

    struct MSTResult {
        vector <pair <int, int>> edges; // edges that make MST (first is vertexA second is vertexB)
        int cost; the MST cost
    }

and return this struct as the result of algorithm's calculation.

Then if I run your .Path method one more time with some other vertex as argument I get (probably) a different MST tree but with the same cost.

2) PriorityQueue: your "PriorityQueue::chgPriority(int index,float priority)" method is not efficient - doing enumeration through the whole queue you lose the benefits of using priority queue. The same goes about your PriorityQueue::contains method which performs linear enumeration so you again lose the value of using priority queue.

Make sure to read this topic on StackOverflow:

http://stackoverflow.com/questions/17009056/how-to-implement-ologn-decrease-key-operation-for-min-heap-based-priority-queu/31123108#31123108

I personally just dropped using chgPriority method as it can be skipped as that topic suggests. See also: http://stackoverflow.com/questions/9255620/why-does-dijkstras-algorithm-use-decrease-key?lq=1.

3) Coding style: you are mostly consistent in your coding style however as far as I know it does not correspond to for example Google C++ Conventions or LLVM coding conventions. I recommend you to try running clang-format tool on your code with default set to either Google C++ or LLVM coding conventions - you'll see how your code looks like if it was written according to their coding guidelines.

4) The following is just advice and I give it to all my classmates on this course: it is not required by assignments on this course but DO WRITE TESTS.

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

If shortestPathDistance is not 5 this test will fail clearly showing you the source line. For this homework I have around 20-30 tests: Graph, PriorityQueue, DijkstraAlgorithm, GraphBuilder - all these classes are covered with basic tests.

I highly encourage you to adopt this approach.

For your interest here is my assignment on Github:

https://github.com/stanislaw/Coursera/tree/294a869330f8621073f8634782472ecce13e3a97/2016.04-05-CPP-for-C-programmers-A/Week%204%2C%20Assignment%203/MinimalSpanningTree/MinimalSpanningTree


I'll put off one point for reusability of algorithm. 

Great work! 

Stanislav
