#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Data_Record
{
    int id;
    string name;
    string address;
    Data_Record* next;

    // Constructor
    Data_Record(int id_value, const string name_value, const string address_value) 
                : id(id_value), name(name_value), address(address_value), next(nullptr) {}
};

class Hash_Table
{
private:
    Data_Record** table;
    int size;
    int num_of_elements;
    const float load_factor_threshold = 0.75;
    
    int hash_function(int id) const;
    void rehash();

public:
    Hash_Table(int table_size);
    ~Hash_Table();

    void insert(int id, const string& name, const string& address);
    Data_Record* search(int id);
    int remove(int id);
    void display() const;
};

#endif