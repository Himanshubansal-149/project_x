// // Function to rebuild the Huffman tree

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
