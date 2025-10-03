#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Open input file in read-only mode
    ifstream inputFile("sample.txt", ios::in);
    if (!inputFile.is_open()) {
        cerr << "Open Failed For Input File" << endl;
        return 1;
    }

    // Open output file in write mode (create if doesn't exist)
    ofstream outputFile("sample - compressed.txt", ios::out);
    if (!outputFile.is_open()) {
        cerr << "Open Failed For Output File" << endl;
        return 1;
    }

    // Optional: Copy contents from input to output
    string line;
    while (getline(inputFile, line)) {
        outputFile << line << '\n';
    }

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
