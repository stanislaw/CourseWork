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

class PriorityQueue {

private:
    vector<int> minHeap;

public:
    PriorityQueue(vector<int> array);

    bool isEmpty();
    void insert(int newValue);
    int getMin();
    void deleteMin();

private:
    void heapify();
    void bubbleDown(int index);
    void bubbleUp(int index);
    void swap(int x, int y);
    
};

void testPriorityQueue();

#endif /* PriorityQueue_h */
