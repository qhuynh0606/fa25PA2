//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        int pos = size;
        data[size++] = idx;

        while (pos > 0) {
            int parent = (pos - 1)/2;
            if (weightArr[pos] < weightArr[parent]) {
                swap(data[pos], data[parent]);
                pos = parent;
            } else {
                break;
            }
        }
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {
            return -1;
        }

        int root = data[0];
        size--;

        int pos = 0;
        while (true) {
            int left = 2*pos + 1;
            int right = 2*pos+2;
            int minIdx = pos;

            if (left < size && weightArr[left] < weightArr[minIdx]) {
                minIdx = left;
            }
            if (right < size && weightArr[right] < weightArr[minIdx]) {
                minIdx = right;
            }
            if (minIdx != pos) {
                swap(data[pos], data[minIdx]);
                pos = minIdx;
            } else {
                break;
            }
        }
        return root; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif