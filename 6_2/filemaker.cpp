    #include <iostream>
    #include <fstream>
    #include <cstdlib> // For rand() and srand()
    #include <ctime>   // For time()

    using namespace std;

    string LAST_LINE = 
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    ;

    void createSpecialFile(const string& filename, int numChars) {
        ofstream outFile((filename + "a" + ".txt"));
        if (!outFile) {
            cout << "Error creating the file: " << filename << endl;
            return;
        }
        for (int i = 0; i < numChars - 1; i++)
        {
            outFile << "a";
        }
        outFile << "b";
        outFile.close();
    }

    void createRandomFile(const string& filename, int numChars) {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(0)));

        // Open the file
        ofstream outFile((filename + ".txt"));
        if (!outFile) {
            cout << "Error creating the file: " << filename << endl;
            return;
        }

        // Generate and write random ASCII characters (printable range: 32-126)
        for (int i = 0; i < numChars; ++i) {
            char randomChar = static_cast<char>(rand() % 94 + 32); // Printable ASCII characters (32-125)
            outFile << randomChar;
        }
        outFile << "\n" << LAST_LINE;
        // Close the file
        outFile.close();
        cout << "File " << filename << " created with " << numChars + LAST_LINE.length() << " random printable ASCII characters + LAST LINE." << endl;
    }

    int main() {
        // Array of file names and their respective character counts
        const int numFiles = 3;
        const string filenames[numFiles] = {"1_000", "100_000", "10_000_000"};
        const int charCounts[numFiles] = {1'000, 100'000, 10'000'000};

        cout << "LAST_LINE = " << LAST_LINE << endl;
        // Create the files
        for (int i = 0; i < numFiles; ++i) {
            createRandomFile("files/" + filenames[i], charCounts[i]);
            createSpecialFile("files/" + filenames[i], charCounts[i]);
        }

        return 0;
    }
