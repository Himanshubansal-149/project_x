// // Function to build Huffman Tree
// struct Node* buildHuffmanTree(char arr[], int freq[],
//     int unique_size)
// {
// struct Node *l, *r, *top;
// while (!isSizeOne(Min_Heap)) {
// l = extractMinFromMin_Heap(Min_Heap);
// r = extractMinFromMin_Heap(Min_Heap);
// top = newNode('$', l->freq + r->freq);
// top->l = l;
// top->r = r;
// insertIntoMin_Heap(Min_Heap, top);
// }
// return extractMinFromMin_Heap(Min_Heap);
// }


// Check if heap size is 1
bool isSizeOne(Min_Heap* heap) {
    return (heap->size == 1);
}

// Extract the minimum node from the heap
Node* extractMinFromMin_Heap(Min_Heap* heap) {
    Node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    Heapify(heap, 0);
    return temp;
}

// Create a new Node
Node* newNode(char c, int freq) {
    Node* temp = new Node(c, freq);
    temp->l = nullptr;
    temp->r = nullptr;
    return temp;
}

// Insert a node into the heap
void insertIntoMin_Heap(Min_Heap* heap, Node* node) {
    heap->size++;
    int i = heap->size - 1;
    
    // Resize vector if necessary
    if (i >= (int)heap->array.size()) {
        heap->array.push_back(node);
    } else {
        heap->array[i] = node;
    }

    // Fix the min heap property going up
    while (i != 0 && heap->array[(i - 1) / 2]->freq > heap->array[i]->freq) {
        swap(heap->array[i], heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to build Huffman Tree
struct Node *buildHuffmanTree(char arr[], int freq[],
    int unique_size)
{
struct Node *l, *r, *top;
Min_Heap* minHeap = createAndBuildMin_Heap(arr, freq, unique_size);
while (!isSizeOne(minHeap))
{
l = extractMinFromMin_Heap(minHeap);
r = extractMinFromMin_Heap(minHeap);
top = newNode('$', l->freq + r->freq);
top->l = l;
top->r = r;
insertIntoMin_Heap(minHeap, top);
}
return extractMinFromMin_Heap(minHeap);
}

