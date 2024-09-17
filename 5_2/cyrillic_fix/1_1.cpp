#include "header_5_2.h"

using namespace std;

string last_names[] = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", 
                     "Попов", "Козлов", "Волков", "Морозов", "Лебедев",
                     "Новиков", "Орлов", "Захаров", "Фёдоров", "Григорьев"};

string first_names[] = {"Александр", "Дмитрий", "Максим", "Алексей", "Иван",
                     "Михаил", "Юрий", "Никита", "Сергей", "Владимир", "Егор",
                      "Павел", "Роман", "Вячеслав", "Олег"};

string father_names[] = {"Александрович", "Дмитриевич", "Максимович", "Алексеевич",
                         "Иванович", "Михайлович", "Юрьевич", "Никитич", "Сергеевич",
                         "Владимирович", "Егорович", "Павлович", "Романович", "Вячеславович",
                         "Олегович"};

string street_names[] = {
        "ул. Ленина", "ул. Сталинская", "ул. Горького", "ул. Пушкина",
        "ул. Чехова", "ул. Тверская", "ул. Маяковского", "ул. Рязанская",
        "пр. Невский", "ул. Арбат", "ул. Суворовская", "пр. Кутузовский",
        "ул. Нагатинская", "ул. Краснопресненская", "пр. Горького"
    };

size_t last_names_size = sizeof(last_names) / sizeof(last_names[0]);
size_t first_names_size = sizeof(first_names) / sizeof(first_names[0]);
size_t father_names_size = sizeof(father_names) / sizeof(father_names[0]);
size_t street_names_size = sizeof(street_names) / sizeof(street_names[0]);

// Padding fields with necessary spaces up to the needed length
void pad_string(const string& str, char* buffer, int size)
{
    memset(buffer, ' ', size);
    strncpy(buffer, str.c_str(), size);
}


int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // setting up random numbers generator
    random_device rd;
    mt19937 eng(rd());

    // define the range for IDs
    uniform_int_distribution<> distr(10000, 99998);

    // opening file to write to
    string output_file_name;
    cout << "Enter output file name (without extension): ";
    cin >> output_file_name;
    output_file_name = FILES_FOLDER + output_file_name;
    string output_file_name_txt = output_file_name + ".txt";
    ofstream output_file(output_file_name_txt);

    if (!output_file.is_open())
    {
        cout << "Unable to open txt file to write.\n";
        return 1;
    }

    // deciding how many entries will be in a file
    int number_of_lines;
    cout << "Enter number of lines to generate: ";
    cin >> number_of_lines;
    auto start_time = chrono::high_resolution_clock::now(); 


    set<int> unique_numbers;

    string line;
    for (int i = 0; i < number_of_lines; i++)
    {

        // making sure generated number wasn't used previously
        int random_number;
        do
        {
            random_number = distr(eng);
            unique_numbers.insert(random_number);
        } while (unique_numbers.size() < i + 1);
        
        // writing the entry
        line = "";
        line += to_string(random_number); // id

        line += DELIMITER;

        line += last_names[distr(eng) % last_names_size];
        line += " ";
        line += first_names[distr(eng) % first_names_size];
        line += " ";
        line += father_names[distr(eng) % father_names_size];

        line += DELIMITER;

        line += street_names[distr(eng) % street_names_size];
        line += " д. ";
        line += to_string(distr(eng) % 120);

        output_file << line << endl;
    } 
    cout << "Successfully written " << number_of_lines << " lines to " << output_file_name_txt << endl;
    // putting special entry at the end
    output_file << SPECIAL_LINE << endl;
    cout << "Sucessfully added special line as the last entry" << endl;

    output_file.close();


    // opening .txt file to read and .bin file to write
    ifstream txtfile(output_file_name_txt);
    ofstream binfile(output_file_name + ".bin", ios::binary);
    
    if (!txtfile.is_open() || !binfile.is_open())
    {
        cout << "Error opening files to convert txt to bin.\n";
        return 1;
    }

    // converting text fields to binary
    while (getline(txtfile, line))
    {
        istringstream iss(line);
        string id_str, name, address;

        getline(iss, id_str, DELIMITER);
        getline(iss, name, DELIMITER);
        getline(iss, address);

        char id_buffer[ID_SIZE];
        char name_buffer[NAME_SIZE];
        char address_buffer[ADDRESS_SIZE];

        pad_string(id_str, id_buffer, ID_SIZE);
        pad_string(name, name_buffer, NAME_SIZE);
        pad_string(address, address_buffer, ADDRESS_SIZE);

        binfile.write(id_buffer, ID_SIZE);
        binfile.write(name_buffer, NAME_SIZE);
        binfile.write(address_buffer, ADDRESS_SIZE);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto time_delta = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Completion time in milliseconds: " << time_delta.count() << endl;
}
