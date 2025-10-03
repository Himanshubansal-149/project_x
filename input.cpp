// // Opening input file in read-only mode
// #include<bits/stdc++.h>
// using namespace std;

// int fd1 = open(“sample.txt”, O_RDONLY);
// if (fd1 == -1) {
//     perror("Open Failed For Input File:\n");
//     exit(1);
// }

// // Creating output file in write mode
// int fd2 = open(“sample - compressed.txt”,
//                O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
// if (fd2 == -1) {
//     perror("Open Failed For Output File:\n");
//     exit(1);
// }


// #include <iostream>
// #include <fstream>
// using namespace std;

// int main() {
//     // Open input file in read-only mode
//     std::ifstream inputFile("sample.txt", std::ios::in);
//     if (!inputFile.is_open()) {
//         std::cerr << "Open Failed For Input File" << std::endl;
//         return 1;
//     }

//     // Open output file in write mode (create if doesn't exist)
//     std::ofstream outputFile("sample - compressed.txt", std::ios::out);
//     if (!outputFile.is_open()) {
//         std::cerr << "Open Failed For Output File" << std::endl;
//         return 1;
//     }

//     // Optional: Copy contents from input to output (just for completeness)
//     std::string line;
//     while (std::getline(inputFile, line)) {
//         outputFile << line << '\n';
//     }

//     // Close files
//     inputFile.close();
//     outputFile.close();

//     return 0;
// }


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
