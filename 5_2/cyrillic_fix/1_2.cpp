#include "header_5_2.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    cout << "Enter name of a binary file (with .bin extension): ";
    string file_name;
    cin >> file_name;
    file_name = FILES_FOLDER + file_name;
    ifstream file(file_name, ios::binary);
    if (!file.is_open())
    {
        cout << "Error openning file.\n";
        return 1;
    }

    char id_buffer[ID_SIZE + 1] = {0};
    char name_buffer[NAME_SIZE + 1] = {0};
    char address_buffer[ADDRESS_SIZE + 1] = {0};

    cout << "Enter key to find: ";
    int key;
    cin >> key;

    auto start_time = chrono::high_resolution_clock::now(); 

    bool found_key = false;
    while (file.read(id_buffer, ID_SIZE))
    {
        file.read(name_buffer, NAME_SIZE);
        file.read(address_buffer, ADDRESS_SIZE);
        int curr_id = stoi(id_buffer);
        if (curr_id == key)
        {
            found_key = true;

            ofstream matches(MATCHES_FILE_NAME);

            string entry = id_buffer;
            entry += DELIMITER;
            
            string curr_name(name_buffer);
            string curr_address(address_buffer);

            curr_name.erase(curr_name.find_last_not_of(' ') + 1);
            curr_address.erase(curr_address.find_last_not_of(' ') + 1);
            
            entry += curr_name;
            entry += DELIMITER;
            
            entry += curr_address;
            matches << entry << endl;
            matches.close();
            file.close();
            break;
        }
    }
    auto end_time = chrono::high_resolution_clock::now(); 
    auto time_delta = chrono::duration_cast<chrono::microseconds>(end_time - start_time); 

    if (found_key) cout << "Match saved to " << MATCHES_FILE_NAME << endl;
    else cout << "No matches found.\n";    
    
    cout << "Completion time in microseconds: " << time_delta.count(); 
    return 0;
}