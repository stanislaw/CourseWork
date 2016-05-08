//
//  PriorityQueue.cpp
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#include "PriorityQueue.h"

#include <cassert>
#include <iostream>

#pragma mark - Tests

void test_initialization_values() {
    PriorityQueue<int> queue = PriorityQueue<int>({3, 111, 112, 1});

    assert(queue.getMin() == 1);
}

void test_isEmpty_withEmptyVector() {
    PriorityQueue<int> queue = PriorityQueue<int>(vector<int>());

    assert(queue.isEmpty());
}

void test_isEmpty_withSomeElements() {
    PriorityQueue<int> queue = PriorityQueue<int>({5, 3, 14});

    assert(queue.isEmpty() == false);
}

void test_insertValue() {
    PriorityQueue<int> queue = PriorityQueue<int>(vector<int>());

    queue.insert(5);

    assert(queue.getMin() == 5);
}

void test_insertValuesWithReversePriority() {
    PriorityQueue<int> queue = PriorityQueue<int>(vector<int>());

    queue.insert(3);
    queue.insert(111);
    queue.insert(112);
    queue.insert(1);

    assert(queue.getMin() == 1);
}

void test_deleteMin() {
    PriorityQueue<int> queue = PriorityQueue<int>(vector<int>());

    queue.insert(111);
    queue.insert(3);
    queue.insert(112);
    queue.insert(1);

    queue.deleteMin();
    assert(queue.getMin() == 3);
}

// This structure is for testing purposes only:
// to test how PriorityQueue works with user-defined types
struct TestPair {

private:
    int vertex;

public:
    TestPair(int vertex) : vertex(vertex) {}

    friend bool operator > (const TestPair& l, const TestPair& r);
    friend bool operator == (const TestPair& l, const TestPair& r);
};

// This is needed to teach PriorityQueue to do comparisons on TestPair
bool operator > (const TestPair& l, const TestPair& r) {
    return l.vertex > r.vertex;
}

// This is to learn how to compare user-defined types (and to see how friends works: 'vertex' can be now made private)
bool operator==(const TestPair& l, const TestPair& r) {
    return l.vertex == r.vertex;
}

void test_userDeclaredTypes() {
    PriorityQueue<TestPair> queue;

    queue.insert(TestPair(4));
    queue.insert(TestPair(3));
    queue.insert(TestPair(5));
    queue.insert(TestPair(1));

    assert(queue.getMin() == TestPair(1));
    queue.deleteMin();
    assert(queue.getMin() == TestPair(3));
    queue.deleteMin();
    assert(queue.getMin() == TestPair(4));
    queue.deleteMin();
    assert(queue.getMin() == TestPair(5));
}

void testPriorityQueue() {
    test_initialization_values();
    test_isEmpty_withEmptyVector();
    test_isEmpty_withSomeElements();

    test_insertValue();
    test_insertValuesWithReversePriority();

    test_deleteMin();

    test_userDeclaredTypes();
}

/**
 https://en.wikipedia.org/wiki/Heap_%28data_structure%29

 0   1  2  3  4 5  6 7 8

 100 19 36 17 3 25 1 2 7

 -   -  -  -  - -  - - -
 100 19 36 17 3 25 1 2 7
 l: 2n + 1
 r: 2n + 2

 n = (l - 1) / 2
 n = (r - 2) / 2
 */

