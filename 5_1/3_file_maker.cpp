#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {
    string file_name;
    int range_start, range_end, num_values;

    // Get user inputs for the file name, range, and the number of unique values
    cout << "Enter the name of the output file: ";
    cin >> file_name;

    cout << "Enter the range start: ";
    cin >> range_start;

    cout << "Enter the range end: ";
    cin >> range_end;

    cout << "Enter how many unique random numbers to generate: ";
    cin >> num_values;

    // Check if we can generate the required number of unique numbers
    if (num_values > (range_end - range_start + 1)) {
        cerr << "Error: More unique values requested than available in the range!" << endl;
        return 1;
    }

    // Create a vector with all the possible numbers in the given range
    vector<int> numbers;
    for (int i = range_start; i <= range_end; i++) {
        numbers.push_back(i);
    }

    // Shuffle the vector to randomize the order
    random_device rd;
    default_random_engine eng(rd());
    shuffle(numbers.begin(), numbers.end(), eng);

    // Open the output file for writing
    ofstream output_file(file_name);
    if (!output_file.is_open()) {
        cerr << "Error: Could not open file " << file_name << " for writing." << endl;
        return 1;
    }

    // Write the first num_values shuffled numbers to the file
    for (int i = 0; i < num_values; i++) {
        output_file << numbers[i] << endl;
    }

    // Close the file
    output_file.close();

    cout << "Random unique numbers have been written to " << file_name << endl;

    return 0;
}
