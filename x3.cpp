// // Structure to store codes in compressed file
// typedef struct code {
//     char k;
//     int l;
//     int code_arr[16];
//     struct code* p;
// } code;

// // Function to print codes into file
// void printCodesIntoFile(int fd2, struct Node* root,
//                         int t[], int top = 0)
// {
//     int i;
//     if (root->l) {
//         t[top] = 0;
//         printCodesIntoFile(fd2, root->l, t, top + 1);
//     }

//     if (root->r) {
//         t[top] = 1;
//         printCodesIntoFile(fd2, root->r, t, top + 1);
//     }

//     if (isLeaf(root)) {
//         data = (code*)malloc(sizeof(code));
//         tree = (Tree*)malloc(sizeof(Tree));
//         data->p = NULL;
//         data->k = root->character;
//         tree->g = root->character;
//         write(fd2, &tree->g, sizeof(char));
//         for (i = 0; i < top; i++) {
//             data->code_arr[i] = t[i];
//         }
//         tree->len = top;
//         write(fd2, &tree->len, sizeof(int));
//         tree->dec
//             = convertBinaryToDecimal(data->code_arr, top);
//         write(fd2, &tree->dec, sizeof(int));
//         data->l = top;
//         data->p = NULL;
//         if (k == 0) {
//             front = rear = data;
//             k++;
//         }
//         else {
//             rear->p = data;
//             rear = rear->p;
//         }
//     }
// }




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
