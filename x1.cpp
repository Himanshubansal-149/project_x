// Function to inititalize and create min_heap 

#include <iostream>
#include <utility>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

// Structure for tree nodes
struct Node {
    char character;
    int freq;
    Node *l, *r;

    Node(char c, int f)
        : character(c)
        , freq(f)
        , l(nullptr)
        , r(nullptr)
    {
    }
};

// Structure for min heap
struct Min_Heap {
    int size;
    vector<Node*> array;

    Min_Heap(int s)
        : size(s)
        , array(s)
    {
    }
};

void Heapify(Min_Heap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
        smallest = left;

    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap(heap->array[idx], heap->array[smallest]);
        Heapify(heap, smallest);
    }
}


// Function to create min heap
Min_Heap* createAndBuildMin_Heap(char arr[], int freq[],
                                 int unique_size)
{
    int i;

    // Initializing heap
    Min_Heap* Mini_Heap = new Min_Heap(unique_size);

    // Initializing the array of pointers in minheap.
    // Pointers pointing to new nodes of character
    // and their frequency
    for (i = 0; i < unique_size; ++i) {
        Mini_Heap->array[i] = new Node(arr[i], freq[i]);
    }

    int n = Mini_Heap->size - 1;
    for (i = (n - 1) / 2; i >= 0; --i) {
        // Standard function for Heap creation
        Heapify(Mini_Heap, i);
    }

    return Mini_Heap;
}