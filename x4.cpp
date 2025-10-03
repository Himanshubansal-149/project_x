// // Function to compress file

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
