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

template <class T>
PriorityQueue<T>::PriorityQueue(vector<T> array) : minHeap(array) {
    heapify();
}

template <class T>
bool PriorityQueue<T>::isEmpty() {
    return minHeap.size() == 0;
}

template <class T>
void PriorityQueue<T>::insert(T newValue) {
    int newIndex = static_cast<int>(minHeap.size());

    minHeap.push_back(newValue);

    bubbleUp(newIndex);
}

template <class T>
T PriorityQueue<T>::getMin() {
    return minHeap[0];
}

template <class T>
void PriorityQueue<T>::deleteMin() {
    int length = static_cast<int>(minHeap.size());

    if (length == 0) {
        return;
    }

    minHeap[0] = minHeap[length-1];
    minHeap.pop_back();

    bubbleDown(0);
}

template <class T>
void PriorityQueue<T>::heapify() {
    int length = static_cast<int>(minHeap.size());

    for(int i = length - 1; i >= 0; --i) {
        bubbleDown(i);
    }
}

template <class T>
void PriorityQueue<T>::bubbleDown(int index) {
    int length = static_cast<int>(minHeap.size());

    int leftChildIndex  = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;

    if (leftChildIndex >= length) {
        return;
    }

    int tempIndex = index;

    if (minHeap[index] > minHeap[leftChildIndex]) {
        tempIndex = leftChildIndex;
    }

    if ((rightChildIndex < length) && (minHeap[tempIndex] > minHeap[rightChildIndex])) {
        tempIndex = rightChildIndex;
    }

    if (tempIndex != index) {
        swap(index, tempIndex);

        bubbleDown(tempIndex);
    }
}

template <class T>
void PriorityQueue<T>::bubbleUp(int index) {
    if (index == 0) {
        return;
    }

    // This division captures both left and right childs
    // Because int / int integer division produces the same parent:
    // n = 13
    // l = 27 => (27 - 1) / 2 = 13
    // r = 28 => (28 - 1) / 2 = 13
    int parentIndex = (index - 1) / 2;

    if (minHeap[parentIndex] > minHeap[index]) {
        swap(parentIndex, index);

        bubbleUp(parentIndex);
    }
}

template <class T>
void PriorityQueue<T>::swap(int x, int y) {
    iter_swap(minHeap.begin() + x, minHeap.begin() + y);
}

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

struct TestPair {

private:
    int vertex;

public:
    TestPair(int vertex) : vertex(vertex) {}

    friend bool operator > (const TestPair& l, const TestPair& r);
    friend bool operator == (const TestPair& l, const TestPair& r);
};

bool operator > (const TestPair& l, const TestPair& r) {
    return l.vertex > r.vertex;
}

bool operator==(const TestPair& l, const TestPair& r) {
    return l.vertex == r.vertex;
}

void test_userTypes_integrationTest() {
    PriorityQueue<TestPair> queue = PriorityQueue<TestPair>(vector<TestPair>());

    queue.insert(TestPair(4));
    queue.insert(TestPair(3));
    queue.insert(TestPair(5));
    queue.insert(TestPair(1));

    assert(queue.getMin() == TestPair(1));
}

void testPriorityQueue() {
    test_isEmpty_withEmptyVector();
    test_isEmpty_withSomeElements();

    test_insertValue();
    test_insertValuesWithReversePriority();

    test_deleteMin();

    test_initialization_values();
    test_userTypes_integrationTest();
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

