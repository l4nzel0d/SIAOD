#include <iostream>
#include <fstream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

string LAST_LINE = "I'm going back to 505";

void createRandomFile(const string& filename, int numChars) {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Open the file
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error creating the file: " << filename << endl;
        return;
    }

    // Generate and write random ASCII characters (printable range: 32-126)
    for (int i = 0; i < numChars; ++i) {
        char randomChar = static_cast<char>(rand() % 95 + 32); // Printable ASCII characters (32-126)
        outFile << randomChar;
    }
    outFile << "\n" << LAST_LINE;
    // Close the file
    outFile.close();
    cout << "File " << filename << " created with " << numChars + LAST_LINE.length() << " random printable ASCII characters + LAST LINE." << endl;
}

int main() {
    // Array of file names and their respective character counts
    const int numFiles = 5;
    const string filenames[numFiles] = { "100.txt", "1000.txt", "10000.txt", "100000.txt", "1000000.txt" };
    const int charCounts[numFiles] = { 100, 1000, 10000, 100000, 1000000 };

    cout << "LAST_LINE = " << LAST_LINE << endl;
    // Create the files
    for (int i = 0; i < numFiles; ++i) {
        createRandomFile(filenames[i], charCounts[i]);
    }

    return 0;
}
