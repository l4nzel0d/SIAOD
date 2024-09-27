#include <iostream>
#include <fstream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

int main() {
    string filename;
    int numChars;

    // Prompt user for filename and number of characters
    cout << "Enter the name of the file to create (with .txt extension): ";
    getline(cin, filename);

    cout << "Enter the number of random ASCII characters to generate: ";
    cin >> numChars;

    // Validate input
    if (numChars <= 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Open the file
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error creating the file: " << filename << endl;
        return 1;
    }

    // Generate and write random ASCII characters (printable range: 32-126)
    for (int i = 0; i < numChars; ++i) {
        char randomChar = static_cast<char>(rand() % 95 + 32); // Printable ASCII characters (32-126)
        outFile << randomChar;
    }
    outFile << "\nSUBSTR";
    // Close the file
    outFile.close();
    cout << "File " << filename << " created with " << numChars << " random printable ASCII characters." << endl;

    return 0;
}
