#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// -------------------- STRUCT DEFINITIONS --------------------
struct Node
{
    char character;
    int freq;
    Node *l, *r;
    Node(char c, int f) : character(c), freq(f), l(nullptr), r(nullptr) {}
};

struct code
{
    char k;
    int l;
    int code_arr[16];
    code *p;
};

struct Tree
{
    char g;
    int len;
    int dec;
    Tree *f;
    Tree *r;
    Tree() : g(0), len(0), dec(0), f(nullptr), r(nullptr) {}
};
// ------------------------------------------------------------

// Globals
int k = 0;
code *front = nullptr;
code *rear = nullptr;

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
bool isSizeOne(Min_Heap *heap)
{
    return (heap->size == 1);
}

// Extract the minimum node from the heap
Node *extractMinFromMin_Heap(Min_Heap *heap)
{
    Node *temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    Heapify(heap, 0);
    return temp;
}

// Create a new Node
Node *newNode(char c, int freq)
{
    Node *temp = new Node(c, freq);
    temp->l = nullptr;
    temp->r = nullptr;
    return temp;
}

// Insert a node into the heap
void insertIntoMin_Heap(Min_Heap *heap, Node *node)
{
    heap->size++;
    int i = heap->size - 1;

    // Resize vector if necessary
    if (i >= (int)heap->array.size())
    {
        heap->array.push_back(node);
    }
    else
    {
        heap->array[i] = node;
    }

    // Fix the min heap property going up
    while (i != 0 && heap->array[(i - 1) / 2]->freq > heap->array[i]->freq)
    {
        swap(heap->array[i], heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to build Huffman Tree
struct Node *buildHuffmanTree(char arr[], int freq[],
                              int unique_size)
{
    struct Node *l, *r, *top;
    Min_Heap *minHeap = createAndBuildMin_Heap(arr, freq, unique_size);
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
// Structure for storing codes in compressed file

// Structure for writing data to file

bool isLeaf(Node *root)
{
    return (root->l == nullptr && root->r == nullptr);
}

int convertBinaryToDecimal(int arr[], int length)
{
    int val = 0;
    for (int i = 0; i < length; i++)
    {
        val = val * 2 + arr[i];
    }
    return val;
}

// isLeaf function prototype
bool isLeaf(Node *root);

// convertBinaryToDecimal function prototype
int convertBinaryToDecimal(int arr[], int length);

void printCodesIntoFile(std::ofstream &outFile, Node *root, int t[], int top = 0)
{
    if (root->l)
    {
        t[top] = 0;
        printCodesIntoFile(outFile, root->l, t, top + 1);
    }

    if (root->r)
    {
        t[top] = 1;
        printCodesIntoFile(outFile, root->r, t, top + 1);
    }

    if (isLeaf(root))
    {
        code *data = new code();
        Tree *tree = new Tree();

        data->p = nullptr;
        data->k = root->character;
        tree->g = root->character;

        // Write the char
        outFile.write(reinterpret_cast<const char *>(&tree->g), sizeof(char));

        for (int i = 0; i < top; i++)
        {
            data->code_arr[i] = t[i];
        }

        tree->len = top;
        outFile.write(reinterpret_cast<const char *>(&tree->len), sizeof(int));

        tree->dec = convertBinaryToDecimal(data->code_arr, top);
        outFile.write(reinterpret_cast<const char *>(&tree->dec), sizeof(int));

        data->l = top;
        data->p = nullptr;

        if (k == 0)
        {
            front = rear = data;
            k++;
        }
        else
        {
            rear->p = data;
            rear = rear->p;
        }

        // Free tree pointer since not used further
        delete tree;
    }
}

void compressFile(std::ifstream &inFile, std::ofstream &outFile, unsigned char a)
{
    char n;
    int h = 0, i;

    // Read one char at a time from input file
    while (inFile.get(n))
    {
        rear = front;
        while (rear->k != n && rear->p != nullptr)
        {
            rear = rear->p;
        }
        if (rear->k == n)
        {
            for (i = 0; i < rear->l; i++)
            {
                if (h < 7)
                {
                    if (rear->code_arr[i] == 1)
                    {
                        a++;
                        a = a << 1;
                        h++;
                    }
                    else if (rear->code_arr[i] == 0)
                    {
                        a = a << 1;
                        h++;
                    }
                }
                else if (h == 7)
                {
                    if (rear->code_arr[i] == 1)
                    {
                        a++;
                        h = 0;
                    }
                    else
                    {
                        h = 0;
                    }
                    outFile.write(reinterpret_cast<const char *>(&a), sizeof(char));
                    a = 0;
                }
            }
        }
    }

    for (i = 0; i < 7 - h; i++)
    {
        a = a << 1;
    }
    outFile.write(reinterpret_cast<const char *>(&a), sizeof(char));

    cout << "Huffman Codes:" << endl;
    code *temp = front;
    while (temp != nullptr)
    {
        cout << temp->k << " : ";
        for (int i = 0; i < temp->l; i++)
        {
            cout << temp->code_arr[i];
        }
        cout << endl;
        temp = temp->p;
    }
}

// Assuming 't', 'tree', 'tree_temp' are declared globally or passed appropriately

void ExtractCodesFromFile(std::ifstream &inFile, Tree *t)
{
    inFile.read(reinterpret_cast<char *>(&t->g), sizeof(char));
    inFile.read(reinterpret_cast<char *>(&t->len), sizeof(int));
    inFile.read(reinterpret_cast<char *>(&t->dec), sizeof(int));
}
constexpr int MAX = 32; // or another suitable max size

void convertDecimalToBinary(int bin[], int dec, int len)
{
    // Convert decimal to binary array (bin[0] is MSB or LSB depending on your convention)
    for (int i = len - 1; i >= 0; i--)
    {
        bin[i] = dec & 1;
        dec >>= 1;
    }
}

Node *ReBuildHuffmanTree(ifstream &inFile, int uniqueCount)
{
    struct Tree t;
    Node *root = new Node('$', 0); // temporary root for Huffman tree

    for (int i = 0; i < uniqueCount; i++)
    {
        // Read one Tree entry from file
        inFile.read(reinterpret_cast<char *>(&t.g), sizeof(char));
        inFile.read(reinterpret_cast<char *>(&t.len), sizeof(int));
        inFile.read(reinterpret_cast<char *>(&t.dec), sizeof(int));

        // Convert decimal code to binary array
        int bin[32] = {0};
        convertDecimalToBinary(bin, t.dec, t.len);

        // Insert this character into the Huffman tree
        Node *cur = root;
        for (int j = 0; j < t.len; j++)
        {
            if (bin[j] == 0)
            {
                if (!cur->l)
                    cur->l = new Node('$', 0);
                cur = cur->l;
            }
            else
            {
                if (!cur->r)
                    cur->r = new Node('$', 0);
                cur = cur->r;
            }
        }
        cur->character = t.g; // set leaf node
    }

    return root; // this is what decompressFile needs
}

bool isLeafNode(Node *n)
{
    return n && n->l == nullptr && n->r == nullptr;
}

void decompressFile(std::ifstream &inFile, std::ofstream &outFile, Node *root, int totalChars)
{
    if (!root)
        return;
    unsigned char byte;
    int written = 0;
    Node *cur = root;

    // Read bytes until we have written totalChars characters
    while (inFile.read(reinterpret_cast<char *>(&byte), 1) && written < totalChars)
    {
        for (int bit = 7; bit >= 0 && written < totalChars; --bit)
        {
            int b = (byte >> bit) & 1;
            cur = b ? cur->r : cur->l;
            if (!cur)
                return; // malformed tree / data
            if (isLeafNode(cur))
            {
                outFile.put(cur->character);
                ++written;
                cur = root;
            }
        }
    }
}

int main()
{
    // ---------- Step 1: Open Input File ----------
    ifstream inputFile("sample.txt", ios::in | ios::binary);
    if (!inputFile.is_open())
    {
        cerr << "Open Failed For Input File" << endl;
        return 1;
    }

    // ---------- Step 2: Count Frequencies ----------
    int freq[256] = {0};
    char ch;
    int totalChars = 0;
    while (inputFile.get(ch))
    {
        freq[(unsigned char)ch]++;
        totalChars++;
    }
    inputFile.clear();
    inputFile.seekg(0); // reset file pointer

    // ---------- Step 3: Prepare Unique Characters ----------
    vector<char> arr;
    vector<int> freqArr;
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            arr.push_back((char)i);
            freqArr.push_back(freq[i]);
        }
    }

    if (arr.empty())
    {
        cerr << "Input file is empty!" << endl;
        return 1;
    }

    // ---------- Step 4: Build Huffman Tree ----------
    Node *root = buildHuffmanTree(arr.data(), freqArr.data(), arr.size());

    // ---------- Step 5: Open Compressed Output ----------
    ofstream compressedFile("sample_compressed.bin", ios::out | ios::binary);
    if (!compressedFile.is_open())
    {
        cerr << "Open Failed For Compressed File" << endl;
        return 1;
    }

    // ---------- Step 6: Write Metadata (unique char count) ----------
    int uniqueCount = arr.size();
    compressedFile.write(reinterpret_cast<const char *>(&uniqueCount), sizeof(int));

    // ---------- Step 7: Write Huffman Codes into File ----------
    int tempArr[100]; // temp for storing binary codes
    printCodesIntoFile(compressedFile, root, tempArr, 0);

    // ---------- Step 8: Compress Original File ----------
    inputFile.clear();
    inputFile.seekg(0);
    compressFile(inputFile, compressedFile, 0); // pass extra params if needed
    compressedFile.close();
    inputFile.close();

    cout << "Compression Done " << endl;

    // ---------- Step 9: Decompress ----------
    ifstream compressedIn("sample_compressed.bin", ios::in | ios::binary);
    ofstream decompressedOut("sample_decompressed.txt", ios::out | ios::binary);

    if (!compressedIn.is_open() || !decompressedOut.is_open())
    {
        cerr << "Failed to open compressed or output file!" << endl;
        return 1;
    }

    // Read unique character count first
    int readUniqueCount;
    compressedIn.read(reinterpret_cast<char *>(&readUniqueCount), sizeof(int));

    // rebuild tree from file using readUniqueCount
    Node *root1 = ReBuildHuffmanTree(compressedIn, readUniqueCount);

    // now decompress actual data
    decompressFile(compressedIn, decompressedOut, root1, totalChars);

    compressedIn.close();
    decompressedOut.close();

    cout << "Decompression Done " << endl;

    cout << "\nDecompressed File Content:" << endl;
    ifstream result("sample_decompressed.txt");
    string line;
    while (getline(result, line))
    {
        cout << line << endl;
    }

    return 0;
}
