// // void decompressFile(int fd1, int fd2, int f)
// // {
// //     int inp[8], i, k = 0;
// //     unsigned char p;
// //     read(fd1, &p, sizeof(char));
// //     convertDecimalToBinary(inp, p, 8);
// //     tree_temp = tree;
// //     for (i = 0; i < 8 && k < f; i++) {
// //         if (!isroot(tree_temp)) {
// //             if (i != 7) {
// //                 if (inp[i] == 0) {
// //                     tree_temp = tree_temp->f;
// //                 }
// //                 if (inp[i] == 1) {
// //                     tree_temp = tree_temp->r;
// //                 }
// //             }
// //             else {
// //                 if (inp[i] == 0) {
// //                     tree_temp = tree_temp->f;
// //                 }
// //                 if (inp[i] == 1) {
// //                     tree_temp = tree_temp->r;
// //                 }
// //                 if (read(fd1, &p, sizeof(char)) != 0) {
// //                     convertDecimalToBinary(inp, p, 8);
// //                     i = -1;
// //                 }
// //                 else {
// //                     break;
// //                 }
// //             }
// //         }
// //         else {
// //             k++;
// //             write(fd2, &tree_temp->g, sizeof(char));
// //             tree_temp = tree;
// //             i--;
// //         }
// //     }
// // }




// #include <fstream>

// // Assuming you have these defined globally or passed in properly:
// extern Tree* tree;          // root of the Huffman tree
// Tree* tree_temp = nullptr;  // temp pointer used in decompression

// bool isroot(Tree* node) {
//     return node->f == nullptr && node->r == nullptr;
// }

// // Binary converter
// void convertDecimalToBinary(int bin[], unsigned char dec, int len) {
//     for (int i = len - 1; i >= 0; i--) {
//         bin[i] = dec & 1;
//         dec >>= 1;
//     }
// }

// // f = number of characters to decode
// void decompressFile(ifstream& inFile, ofstream& outFile, int f) {
//     int inp[8], i, k = 0;
//     unsigned char p;

//     // Read the first byte
//     if (!inFile.read(reinterpret_cast<char*>(&p), sizeof(char))) return;

//     convertDecimalToBinary(inp, p, 8);

//     tree_temp = tree;

//     for (i = 0; i < 8 && k < f; i++) {
//         if (!isroot(tree_temp)) {
//             if (inp[i] == 0) {
//                 tree_temp = tree_temp->f;
//             } else if (inp[i] == 1) {
//                 tree_temp = tree_temp->r;
//             }

//             // If last bit in byte
//             if (i == 7) {
//                 if (inFile.read(reinterpret_cast<char*>(&p), sizeof(char))) {
//                     convertDecimalToBinary(inp, p, 8);
//                     i = -1; // reset i to -1, next loop i++ becomes 0
//                 } else {
//                     break; // End of file
//                 }
//             }
//         } else {
//             k++;
//             outFile.write(reinterpret_cast<const char*>(&tree_temp->g), sizeof(char));
//             tree_temp = tree;
//             i--;  // stay at same bit to reprocess
//         }
//     }
// }


bool isLeafNode(Node* n) {
    return n && n->l == nullptr && n->r == nullptr;
}

void decompressFile(std::ifstream& inFile, std::ofstream& outFile, Node* root, int totalChars)
{
    if (!root) return;
    unsigned char byte;
    int written = 0;
    Node* cur = root;

    // Read bytes until we have written totalChars characters
    while (inFile.read(reinterpret_cast<char*>(&byte), 1) && written < totalChars) {
        for (int bit = 7; bit >= 0 && written < totalChars; --bit) {
            int b = (byte >> bit) & 1;
            cur = b ? cur->r : cur->l;
            if (!cur) return;               // malformed tree / data
            if (isLeafNode(cur)) {
                outFile.put(cur->character);
                ++written;
                cur = root;
            }
        }
    }
}
