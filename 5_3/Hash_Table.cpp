#include "Hash_Table.h"

Hash_Table::Hash_Table(int table_size) : size(table_size), num_of_elements(0)
{
    table = new Data_Record*[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;
    }
}

Hash_Table::~Hash_Table()
{
    for (int i = 0; i < size; i++)
    {
        Data_Record* current = table[i];
        while (current != nullptr)
        {
            Data_Record* temp = current;
            current = current->next;
            delete temp;
        }

    }
    delete[] table;
}

int Hash_Table::hash_function(int id) const
{
    return id % size;
}

void Hash_Table::rehash()
{
    cout << "Rehashing: increasing table size to " << size * 2 << endl;
    int old_size = size;

    // Creating new empty table of twice the size
    size *= 2;
    Data_Record** new_table = new Data_Record*[size];
    for (int i = 0; i < size; i++)
    {
        new_table[i] = nullptr;
    }

    // Moving data from old table to the new
    for (int i = 0; i < old_size; i++)
    {
        Data_Record* current = table[i];
        while (current != nullptr)
        {
            int new_index = hash_function(current->id);
            Data_Record* next_record = current->next;

            current->next = new_table[new_index];
            new_table[new_index] = current;

            current = next_record;
        }
    }

    delete[] table;
    table = new_table;
}


int Hash_Table::insert(int id, const string& name, const string& address)
{
    int index = hash_function(id);
    Data_Record* new_record = new Data_Record(id, name, address);

    new_record->next = table[index];
    table[index] = new_record;

    num_of_elements++;
    if ((static_cast<float>(num_of_elements) / size) > load_factor_threshold)
    {
        rehash();
    }

}

Data_Record* Hash_Table::search(int id)
{
    int index = hash_function(id);
    Data_Record* current = table[index];
    while (current != nullptr)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int Hash_Table::remove(int id)
{
    int index = hash_function(id);
    Data_Record* current = table[index];
    Data_Record* prev = nullptr;

    while (current != nullptr)
    {
        if (current->id == id)
        {
            // Element to delete is first in chain
            if (prev == nullptr)
            {
                table[index] = current->next;
            }

            else
            {
                prev->next = current->next;
            }
            delete current;
            num_of_elements--;
            return 0; // Return code: data record successfully deleted
        }
        prev = current;
        current = current->next;
    }
    return 1; // Return code: data record not found
}

void Hash_Table::display() const
{
    for (int i = 0; i < size; i++)
    {
        Data_Record* current = table[i];
        if (current != nullptr)
        {
            cout << "Index " << i << ": ";
            while (current != nullptr)
            {
                cout << " [номер читательского билета: " << current->id
                     << ", ФИО: " << current->name
                     << ", Адрес: " << current->address << "] ";
                current = current->next;
            }
            cout << endl;
        }
    }
}