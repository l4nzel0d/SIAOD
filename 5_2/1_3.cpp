#include "header_5_2.h"

using namespace std;

// Necessary function for sorting lookup table 
bool cmpr_columns(const array<int, 2>& a, const array<int, 2>& b, int col_index)
{
    return a[col_index] < b[col_index];
}

// The search in lookup table
int uniform_binary_search(vector<array<int, 2>>& vec, int target)
{
    int n = vec.size();
    int pow = 1;
    int offset;
    int curr_position = 0;
    do
    {
        pow <<= 1;

        offset = (n + (pow >> 1)) / pow;

        if (vec[curr_position][0] == target)
        {
            return curr_position;
        }
        else if (vec[curr_position][0] < target)
        {
            curr_position += offset;
        }
        else
        {
            curr_position -= offset;
        }        
    } while (offset > 0);
    return -1;
}

// Getting formatted entry
string get_entry(string file_name, streampos position_in_file)
{
    char id_buffer[ID_SIZE + 1] = {0};
    char name_buffer[NAME_SIZE + 1] = {0};
    char address_buffer[ADDRESS_SIZE + 1] = {0};

    ifstream file(file_name, ios::binary);
    file.seekg(position_in_file);
    file.read(id_buffer, ID_SIZE);
    file.read(name_buffer, NAME_SIZE);
    file.read(address_buffer, ADDRESS_SIZE);
    file.close();

    string entry = id_buffer;
    entry += DELIMITER;
    
    string curr_name(name_buffer);
    string curr_address(address_buffer);

    curr_name.erase(curr_name.find_last_not_of(' ') + 1);
    curr_address.erase(curr_address.find_last_not_of(' ') + 1);
    
    entry += curr_name;
    entry += DELIMITER;
    
    entry += curr_address;
    return entry;
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Opening relevant data file
    cout << "Enter name of a binary file (with .bin extension): ";
    string file_name;
    cin >> file_name;
    file_name = FILES_FOLDER + file_name;
    ifstream file(file_name, ios::binary | ios::ate);
    if (!file.is_open())
    {
        cout << "Error openning file.\n";
        return 1;
    }

    const streampos file_size = file.tellg(); // Getting file size
    const size_t line_length = ID_SIZE + NAME_SIZE + ADDRESS_SIZE; 
    const size_t number_of_entries = file_size / line_length;
    
    // Declaring a lookup table
    vector<array<int, 2>> lookup_table(number_of_entries);

    // Creating char buffers for each of the fields of an entry
    char id_buffer[ID_SIZE + 1] = {0};


    // Filling lookup table with data {ID, byte_position in file}
    for (int i = 0; i < number_of_entries; i++)
    {
        streampos curr_position = i*line_length;
        file.seekg(curr_position);
        file.read(id_buffer, ID_SIZE);
        lookup_table[i][0] = stoi(id_buffer);
        lookup_table[i][1] = curr_position;
    }
    file.close();

    // Sorting lookup table
    const int col_index = 0; 
    sort(lookup_table.begin(), lookup_table.end(), [col_index](const array<int, 2>& a, const array<int, 2>& b) {
        return cmpr_columns(a, b, col_index);
    });

    // Getting key value to look for
    cout << "Enter key to find: ";
    int key;
    cin >> key;

    // Starting timer
    auto start_time = chrono::high_resolution_clock::now(); 

    // Search in lookup table
    int position = uniform_binary_search(lookup_table, key);
    auto end_time = chrono::high_resolution_clock::now();
    auto time_delta = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
    if (position == -1)
    {
        cout << "Key not found.\n";
        return 1;
    }

    // Accessing relevant entry from a file
    streampos position_in_file = lookup_table[position][1];
    string entry = get_entry(file_name, position_in_file);

    ofstream matches(MATCHES_FILE_NAME);
    matches << entry << endl;
    cout << "Match saved to " << MATCHES_FILE_NAME << endl;

    // Showing search time
    cout << "Completion time in nanoseconds: " << time_delta.count();

    matches.close();
}
