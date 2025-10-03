// #include <iostream>
// #include <fstream>
// #include <string>
#include <bits/stdc++.h>

using namespace std;

// Structure for tree nodes
struct Node
{
    char character;
    int freq;
    Node *l, *r;

    Node(char c, int f)
        : character(c), freq(f), l(nullptr), r(nullptr)
    {
    }
};

// Structure for min heap
struct Min_Heap
{
    int size;
    vector<Node *> array;

    Min_Heap(int s)
        : size(s), array(s)
    {
    }
};

void Heapify(Min_Heap *heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
        smallest = left;

    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swap(heap->array[idx], heap->array[smallest]);
        Heapify(heap, smallest);
    }
}

// Function to create min heap
Min_Heap *createAndBuildMin_Heap(char arr[], int freq[],
                                 int unique_size)
{
    int i;

    // Initializing heap
    Min_Heap *Mini_Heap = new Min_Heap(unique_size);

    // Initializing the array of pointers in minheap.
    // Pointers pointing to new nodes of character
    // and their frequency
    for (i = 0; i < unique_size; ++i)
    {
        Mini_Heap->array[i] = new Node(arr[i], freq[i]);
    }

    int n = Mini_Heap->size - 1;
    for (i = (n - 1) / 2; i >= 0; --i)
    {
        // Standard function for Heap creation
        Heapify(Mini_Heap, i);
    }

    return Mini_Heap;
}


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



int k = 0;
code* front = nullptr;
code* rear = nullptr;

bool isLeaf(Node* root) {
    return (root->l == nullptr && root->r == nullptr);
}

int convertBinaryToDecimal(int arr[], int length) {
    int val = 0;
    for (int i = 0; i < length; i++) {
        val = val * 2 + arr[i];
    }
    return val;
}



#include <fstream>

// Assuming these globals and functions exist somewhere else:
extern int k;            // global counter as in your code
extern code* front;      // global pointer
extern code* rear;       // global pointer

// isLeaf function prototype
bool isLeaf(Node* root);

// convertBinaryToDecimal function prototype
int convertBinaryToDecimal(int arr[], int length);

// Structure for storing codes in compressed file
struct code {
    char k;
    int l;
    int code_arr[16];
    code* p;
};

// Structure for writing data to file
struct Tree {
    char g;
    int len;
    int dec;
};

void printCodesIntoFile(std::ofstream& outFile, Node* root, int t[], int top = 0)
{
    if (root->l) {
        t[top] = 0;
        printCodesIntoFile(outFile, root->l, t, top + 1);
    }

    if (root->r) {
        t[top] = 1;
        printCodesIntoFile(outFile, root->r, t, top + 1);
    }

    if (isLeaf(root)) {
        code* data = new code();
        Tree* tree = new Tree();

        data->p = nullptr;
        data->k = root->character;
        tree->g = root->character;

        // Write the char
        outFile.write(reinterpret_cast<const char*>(&tree->g), sizeof(char));

        for (int i = 0; i < top; i++) {
            data->code_arr[i] = t[i];
        }

        tree->len = top;
        outFile.write(reinterpret_cast<const char*>(&tree->len), sizeof(int));

        tree->dec = convertBinaryToDecimal(data->code_arr, top);
        outFile.write(reinterpret_cast<const char*>(&tree->dec), sizeof(int));

        data->l = top;
        data->p = nullptr;

        if (k == 0) {
            front = rear = data;
            k++;
        }
        else {
            rear->p = data;
            rear = rear->p;
        }

        // Free tree pointer since not used further
        delete tree;
    }
}


#include <fstream>

// Assume these globals exist, as in your code:
extern code* front;
extern code* rear;

void compressFile(std::ifstream& inFile, std::ofstream& outFile, unsigned char a)
{
    char n;
    int h = 0, i;

    // Read one char at a time from input file
    while (inFile.get(n)) {
        rear = front;
        while (rear->k != n && rear->p != nullptr) {
            rear = rear->p;
        }
        if (rear->k == n) {
            for (i = 0; i < rear->l; i++) {
                if (h < 7) {
                    if (rear->code_arr[i] == 1) {
                        a++;
                        a = a << 1;
                        h++;
                    }
                    else if (rear->code_arr[i] == 0) {
                        a = a << 1;
                        h++;
                    }
                }
                else if (h == 7) {
                    if (rear->code_arr[i] == 1) {
                        a++;
                        h = 0;
                    }
                    else {
                        h = 0;
                    }
                    outFile.write(reinterpret_cast<const char*>(&a), sizeof(char));
                    a = 0;
                }
            }
        }
    }

    for (i = 0; i < 7 - h; i++) {
        a = a << 1;
    }
    outFile.write(reinterpret_cast<const char*>(&a), sizeof(char));
}


#include <fstream>

// Use this struct in C++ style
struct Tree {
    char g;
    int len;
    int dec;
    Tree* f;
    Tree* r;

    Tree() : g(0), len(0), dec(0), f(nullptr), r(nullptr) {}  // constructor
};

// Assuming 't', 'tree', 'tree_temp' are declared globally or passed appropriately

void ExtractCodesFromFile(std::ifstream& inFile, Tree* t)
{
    inFile.read(reinterpret_cast<char*>(&t->g), sizeof(char));
    inFile.read(reinterpret_cast<char*>(&t->len), sizeof(int));
    inFile.read(reinterpret_cast<char*>(&t->dec), sizeof(int));
}
constexpr int MAX = 32;  // or another suitable max size

void convertDecimalToBinary(int bin[], int dec, int len) {
    // Convert decimal to binary array (bin[0] is MSB or LSB depending on your convention)
    for (int i = len - 1; i >= 0; i--) {
        bin[i] = dec & 1;
        dec >>= 1;
    }
}



void ReBuildHuffmanTree(ifstream& inFile, int size)
{
    

    Tree* tree = new Tree();
    Tree* tree_temp = tree;
    Tree* t = new Tree();

    for (int k = 0; k < size; k++) {
        tree_temp = tree;
        ExtractCodesFromFile(inFile, t);

        int bin[MAX] = {0}, bin_con[MAX] = {0};
        convertDecimalToBinary(bin, t->dec, t->len);

        for (int i = 0; i < t->len; i++) {
            bin_con[i] = bin[i];
        }

        for (int j = 0; j < t->len; j++) {
            if (bin_con[j] == 0) {
                if (tree_temp->f == nullptr) {
                    tree_temp->f = new Tree();
                }
                tree_temp = tree_temp->f;
            }
            else { // bin_con[j] == 1
                if (tree_temp->r == nullptr) {
                    tree_temp->r = new Tree();
                }
                tree_temp = tree_temp->r;
            }
        }
        tree_temp->g = t->g;
        tree_temp->len = t->len;
        tree_temp->dec = t->dec;
        tree_temp->f = nullptr;
        tree_temp->r = nullptr;
    }

    delete t; // free temporary node if not needed further

    // Use 'tree' as the rebuilt Huffman tree root
}

#include <fstream>

// Assuming you have these defined globally or passed in properly:
extern Tree* tree;          // root of the Huffman tree
Tree* tree_temp = nullptr;  // temp pointer used in decompression

bool isroot(Tree* node) {
    return node->f == nullptr && node->r == nullptr;
}

// Binary converter
void convertDecimalToBinary(int bin[], unsigned char dec, int len) {
    for (int i = len - 1; i >= 0; i--) {
        bin[i] = dec & 1;
        dec >>= 1;
    }
}

// f = number of characters to decode
void decompressFile(ifstream& inFile, ofstream& outFile, int f) {
    int inp[8], i, k = 0;
    unsigned char p;

    // Read the first byte
    if (!inFile.read(reinterpret_cast<char*>(&p), sizeof(char))) return;

    convertDecimalToBinary(inp, p, 8);

    tree_temp = tree;

    for (i = 0; i < 8 && k < f; i++) {
        if (!isroot(tree_temp)) {
            if (inp[i] == 0) {
                tree_temp = tree_temp->f;
            } else if (inp[i] == 1) {
                tree_temp = tree_temp->r;
            }

            // If last bit in byte
            if (i == 7) {
                if (inFile.read(reinterpret_cast<char*>(&p), sizeof(char))) {
                    convertDecimalToBinary(inp, p, 8);
                    i = -1; // reset i to -1, next loop i++ becomes 0
                } else {
                    break; // End of file
                }
            }
        } else {
            k++;
            outFile.write(reinterpret_cast<const char*>(&tree_temp->g), sizeof(char));
            tree_temp = tree;
            i--;  // stay at same bit to reprocess
        }
    }
}



int main()
{
    // Open input file in read-only mode
    ifstream inputFile("sample.txt", ios::in);
    if (!inputFile.is_open())
    {
        cerr << "Open Failed For Input File" << endl;
        return 1;
    }

    // Open output file in write mode (create if doesn't exist)
    ofstream outputFile("sample - compressed.txt", ios::out);
    if (!outputFile.is_open())
    {
        cerr << "Open Failed For Output File" << endl;
        return 1;
    }

    // Optional: Copy contents from input to output
    string line;
    while (getline(inputFile, line))
    {
        outputFile << line << '\n';
    }

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
