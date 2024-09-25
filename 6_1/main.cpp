#include "Hash_Table.h"
#include <limits>

Hash_Table library(5);

void add_initial_records()
{
    library.insert(new Data_Record(64196, "Григорьев Егор Алексеевич", "ул. Ленина д. 115"));
    library.insert(new Data_Record(71178, "Иванов Михаил Вячеславович", "ул. Краснопресненская д. 35"));
    library.insert(new Data_Record(21339, "Смирнов Максим Никитич", "ул. Арбат д. 101"));
    library.insert(new Data_Record(88642, "Морозов Сергей Павлович", "ул. Тверская д. 72"));
    library.insert(new Data_Record(76992, "Орлов Михаил Юрьевич", "ул. Чехова д. 119"));
    library.insert(new Data_Record(28979, "Сидоров Дмитрий Павлович", "ул. Суворовская д. 14"));
    library.insert(new Data_Record(57118, "Новиков Алексей Вячеславович", "пр. Горького д. 39"));
}

void clear_cin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


int get_id_from_user()
{
    int id;
    while (true)
    {
        cout << "Enter id (5 digit number): ";
        if (cin >> id && id >= 10000 && id <= 99999)
        {
            clear_cin();
            return id;
        } 
        clear_cin();
        cout << "Invalid id\n";
    }
}


string get_string_from_user(string prompt)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

void insert()
{
    int id = get_id_from_user();
    string name = get_string_from_user("Enter name: ");
    string address = get_string_from_user("Enter address: ");
    Data_Record* new_record = new Data_Record(id, name, address);
    library.insert(new_record);
    cout << "Successfully inserted record: " << new_record->string_rep() << endl;
};

void del() 
{
    int id = get_id_from_user();
    int return_code = library.remove(id);
    if (return_code == 0)
    {
        cout << "Record with id = " << id << " was successfully deleted" << endl;
    }
    else
    {
        cout << "Record with id = " << id << " wasn't found" << endl;
    }
};

void search() 
{
    int id = get_id_from_user();
    Data_Record* record = library.search(id);
    if (record == nullptr)
    {
        cout << "Record with id = " << id << " not found" << endl;
        return;
    }
    cout << "Found record: " << record->string_rep() << endl;

};

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    add_initial_records();

    int cmd;
    while (true)
    {
        while (true)
        {
            cout << "\n\t-- Enter Your Command Code --" << endl;
            cout << "1: Insert" << endl;
            cout << "2: Delete" << endl;
            cout << "3: Search" << endl;
            cout << "4: Display" << endl;
            cout << "0: Exit" << endl;
            cout << "\tCommand Code: ";
            if (cin >> cmd && cmd >= 0 && cmd <= 4) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Command Code\n";
        }


        switch(cmd)
        {
            case 0: 
                cout << "Exiting...";
                return 0;
            case 1:
                insert();
                break;
            case 2: 
                del();
                break;
            case 3:
                search();
                break;
            case 4: 
                library.display();
                break;
        }
    }
}