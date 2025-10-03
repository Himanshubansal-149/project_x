#include <bits/stdc++.h>
using namespace std;

// -------------------- NODE STRUCT --------------------
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // smallest frequency has priority
    }
};

// -------------------- HUFFMAN FUNCTIONS --------------------

// Build Huffman Tree
Node* buildHuffmanTree(const unordered_map<char,int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (const auto &p : freqMap) {
        pq.push(new Node(p.first, p.second));
    }
    

    while(pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* parent = new Node('$', l->freq + r->freq);
        parent->left = l;
        parent->right = r;
        pq.push(parent);
    }
    return pq.top();
}

// Generate Huffman Codes
void generateCodes(Node* root, string code, unordered_map<char,string>& codes) {
    if(!root) return;
    if(!root->left && !root->right) { // leaf
        codes[root->ch] = code;
        return;
    }
    generateCodes(root->left, code+"0", codes);
    generateCodes(root->right, code+"1", codes);
}

// Compress input file to output file
void compressFile(const string& inputFile, const unordered_map<char,string>& codes, const string& outputFile) {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);

    string bitstream;
    char ch;
    while(fin.get(ch)) bitstream += codes.at(ch);

    unsigned char byte = 0;
    int count = 0;
    for(char b : bitstream) {
        byte <<= 1;
        if(b=='1') byte |= 1;
        count++;
        if(count==8) { fout.put(byte); byte=0; count=0; }
    }
    if(count) { byte <<= (8-count); fout.put(byte); } // last byte
}

// Check if leaf
bool isLeaf(Node* node) { return node && !node->left && !node->right; }

// Decompress file
void decompressFile(const string& inputFile, const string& outputFile, Node* root, int totalChars) {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);

    Node* cur = root;
    char byte;
    int written = 0;

    while(fin.get(byte) && written < totalChars) {
        for(int i=7; i>=0 && written<totalChars; i--) {
            int bit = (byte >> i) & 1;
            cur = bit ? cur->right : cur->left;
            if(!cur) return; // corrupted data
            if(isLeaf(cur)) {
                fout.put(cur->ch);
                written++;
                cur = root;
            }
        }
    }
}

// -------------------- MAIN --------------------
int main() {
    string inputFile = "sample.txt";
    string compressedFile = "compressed.bin";
    string decompressedFile = "decompressed.txt";

    // Step 1: Count frequencies
    ifstream fin(inputFile, ios::binary);
    unordered_map<char,int> freqMap;
    char ch;
    int totalChars = 0;
    while(fin.get(ch)) { freqMap[ch]++; totalChars++; }
    fin.close();

    if(freqMap.empty()) { cerr << "Empty input file!\n"; return 1; }

    // Step 2: Build Huffman Tree
    Node* root = buildHuffmanTree(freqMap);

    // Step 3: Generate Codes
    unordered_map<char,string> codes;
    generateCodes(root, "", codes);

    cout << "Huffman Codes:\n";
    for(const auto &p : codes) {
        cout << p.first << " : " << p.second << "\n";
    }
    

    // Step 4: Compress
    compressFile(inputFile, codes, compressedFile);
    cout << "\nCompression Done \n";

    // Step 5: Decompress
    decompressFile(compressedFile, decompressedFile, root, totalChars);
    cout << "Decompression Done \n";

    // Step 6: Show decompressed content
    ifstream res(decompressedFile);
    cout << "\nDecompressed File Content:\n";
    string line;
    while(getline(res, line)) cout << line << endl;

    return 0;
}
