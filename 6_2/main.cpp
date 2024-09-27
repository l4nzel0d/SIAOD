#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <string.h>

using namespace std;

int NOT_FOUND_INDEX = -1;
const int ALPHABET_SIZE = 256;
int COMPARISONS = 0;

// Search for the FIRST occurence of needle in haystack
int linear_search(const string& haystack, const string& needle)
{
    int i = 0;
    int j = 0;
    int lh = haystack.length();
    int ln = needle.length();

    if (lh < ln) // Needle is longer than Haystack
    {
        return NOT_FOUND_INDEX; // Unsuccessful search
    }

    // Iterating over characters in Haystack
    for (int i = 0; i <= lh - ln; i++) 
    {
        int j = 0;
        while (j < ln && haystack[i + j] == needle[j]) 
        {
            COMPARISONS++;
            j++;
        }
        COMPARISONS++;

        // Succesful search
        if (j == ln) return i; 
    }
    return NOT_FOUND_INDEX; // Unsuccessful search
}

void fill_char_shift_table(const string& needle, int char_shift_table[])
{
    int ln = needle.length();

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        char_shift_table[i] = ln;
    }

    for (int i = 0; i < needle.length() - 1; i++)
    {
        char_shift_table[static_cast<unsigned char>(needle[i])] = ln - 1 - i;
    } 

}

// Search for the LAST occurence of needle in haystack
int bmh_search(const string& haystack, const string& needle)
{
    int lh = haystack.length();
    int ln = needle.length();
    int last_occurence_index = NOT_FOUND_INDEX;

    if (lh < ln) // Needle is longer than Haystack
    {
        return NOT_FOUND_INDEX; // Unsuccessful search
    }

    int char_shift_table[ALPHABET_SIZE];
    fill_char_shift_table(needle, char_shift_table);
    int i = 0;

    while (i <= lh - ln)
    {
        int j = ln - 1;

        while (j >= 0 && haystack[i+j] == needle[j])
        {
            COMPARISONS++;
            j--;
        }
        COMPARISONS++;

        if (j < 0) last_occurence_index = i;
        // Determine shift
        // Mismatch at the last character of the needle
        if (j == ln - 1)
        {
            // Shift based on the mismatched character from haystack
            i += char_shift_table[static_cast<unsigned char>(haystack[i+j])];
        } 
        // Mismatch left of the last character of the needle
        else
        {
            // Shift based on the last character of the needle 
            i+= char_shift_table[static_cast<unsigned char>(needle[ln - 1])];
        }
    }
    return last_occurence_index;

}

int main()
{
    string filename; // Where we search


    // Get name of Haystack file
    cout << "Enter name of textfile (haystack) with .txt: ";
    getline(cin, filename);

    // Opening file
    ifstream file(filename);
    if (!file.is_open()) // If failed to open
    {
        cout << "Couldn't open file: " << filename << endl;
        return 1;
    }

    // Reading the whole file into Haystack string
    string haystack;
    string line;
    while (getline(file, line))
    {
        haystack += line + "\n";
    }

    // Closing file
    file.close();


    // Get Needle from user
    string needle; // What we search
    cout << "Enter substring to search for (needle): ";
    getline(cin, needle);

    // Propmting user to choose search option
    int search_option;
    cout << "\t---Search options---" << endl;
    cout << "1 - Linear search to find the first match" << endl;
    cout << "2 - Boyer-Moore-Horspool search to find the last match" << endl;
    cout << "Which search to use: ";
    cin >> search_option;

    // Executing chosen search
    int found_index;
    auto start_time = chrono::high_resolution_clock::now();
    switch(search_option)
    {
        case 1:
            found_index = linear_search(haystack, needle);
            break;

        case 2:
            found_index = bmh_search(haystack, needle);
            break;
    }
    auto end_time = chrono::high_resolution_clock::now();   
    auto time_delta = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Search completed in " << time_delta.count() << " microseconds" << endl;
    cout << "Total number of comparisons made " << COMPARISONS << endl;
    cout << "Needle: \"" << needle << "\"";
    if (found_index == NOT_FOUND_INDEX)
    {
        cout << " was not found in textfile" << endl;
        return 1;
    }

    cout <<  " was found at index: " << found_index << endl;
    return 0;
}