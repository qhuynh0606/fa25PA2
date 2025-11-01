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

    // Implements min heap to store nodes. Used to extract the smallest weight nodes
    MinHeap() { size = 0; }

    // insert index at end of heap, restore order using upheap()
    // organized by weight from weightArr[]
    void push(int idx, int weightArr[]) {
        int pos = size;
        data[size++] = idx;

        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                std::swap(data[pos], data[parent]);
                pos = parent;
            } else {
                break;
            }
        }
    }

    // remove and return smallest index
    // Replace root with last element, then call downheap()
    // after removal, heap property restored by bubbling down
    int pop(int weightArr[]) {
        if (size == 0) {
            return -1;
        }

        int root = data[0];

        data[0] = data[size - 1];
        size--;

        int pos = 0;
        while (true) {
            int left  = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;

            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) {
                smallest = left;
            }
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
                smallest = right;
            }
            if (smallest != pos) {
                std::swap(data[pos], data[smallest]);
                pos = smallest;
            } else {
                break;
            }
        }
        return root;
    }

    // swap child upward while smaller than parent until heap property restored
    // usually called after inserting new node
    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                std::swap(data[pos], data[parent]);
                pos = parent;
            } else {
                break;
            }
        }
    }

    // swap parent downward while larger than any child
    // usually called after removing element
    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = pos;

            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) {
                smallest = left;
            }
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
                smallest = right;
            }

            if (smallest != pos) {
                std::swap(data[pos], data[smallest]);
                pos = smallest;
            } else {
                break;
            }
        }
    }
};

#endif