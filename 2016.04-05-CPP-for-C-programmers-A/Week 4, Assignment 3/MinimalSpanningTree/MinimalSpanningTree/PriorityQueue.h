//
//  PriorityQueue.h
//  DijkstraAlgorithm
//
//  Created by Stanislaw Pankevich on 30/04/16.
//  Copyright © 2016 Stanislaw Pankevich. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <vector>

using namespace std;

// Min Binary Heap Implementation in C++
//
// Based on:
// http://www.codeproject.com/Tips/816934/Min-Binary-Heap-Implementation-in-Cplusplus#_comments
//
template <class T>
class PriorityQueue {

private:
    vector<T> minHeap;

public:
    PriorityQueue(vector<T> array);

    bool isEmpty();
    void insert(T newValue);
    T getMin();
    void deleteMin();

private:
    void heapify();
    void bubbleDown(int index);
    void bubbleUp(int index);
    void swap(int x, int y);
};

void testPriorityQueue();

#endif /* PriorityQueue_h */
