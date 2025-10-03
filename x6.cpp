// Function to decompress the corresponding output 


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
