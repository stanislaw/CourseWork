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
    PriorityQueue() : minHeap() {}

    PriorityQueue(vector<T> array) : minHeap(array) {
        heapify();
    }

    bool isEmpty() {
        return minHeap.size() == 0;
    }

    void insert(T newValue) {
        int newIndex = static_cast<int>(minHeap.size());

        minHeap.push_back(newValue);

        bubbleUp(newIndex);
    }

    T getMin() {
        // I am not sure what is a good practice in CPP to handle this case
        // I was thinking about returning default constructor: T() but
        // that can cause ambiguity for some types of T
        // So here I prefer to fail early to know that something is going wrong
        // if one tries to get an element from empty queue
        if (isEmpty()) {
            throw "Queue is empty!";
        }

        return minHeap[0];
    }

    void deleteMin() {
        int length = static_cast<int>(minHeap.size());

        if (length == 0) {
            return;
        }

        minHeap[0] = minHeap[length-1];
        minHeap.pop_back();

        bubbleDown(0);
    }

private:

    void heapify() {
        int length = static_cast<int>(minHeap.size());

        for(int i = length - 1; i >= 0; --i) {
            bubbleDown(i);
        }
    }

    void bubbleDown(int index) {
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

    void bubbleUp(int index) {
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
    
    void swap(int x, int y) {
        iter_swap(minHeap.begin() + x, minHeap.begin() + y);
    }
};

void testPriorityQueue();

#endif /* PriorityQueue_h */
