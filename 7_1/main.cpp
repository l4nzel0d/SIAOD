#include "RBTree.h"
#include <limits>

// Initializing empty Red-Black Tree
#define DATA_TYPE int

RedBlackTree<DATA_TYPE> rbtree;

// Utility function for correctly clearing input stream
void clear_cin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void add_initial_nodes()
{
    rbtree.insert(13);
    rbtree.insert(8);
    rbtree.insert(17);
    rbtree.insert(1);
    rbtree.insert(11);
    rbtree.insert(15);
    rbtree.insert(25);
    rbtree.insert(6);
    rbtree.insert(22);
    rbtree.insert(27);
}

template <typename T>
T get_key(const string& prompt)
{
    T key;
    while (true)
    {
        cout << prompt;
        if (cin >> key)
        {
            clear_cin();
            return key;
        }
        clear_cin();
        cout << "Invalid input. Please try again.\n";
    }
}

void insert()
{
    cout << "||| Inserting Operation |||" << endl;
    DATA_TYPE key = get_key<DATA_TYPE>("Enter value to insert: ");
    rbtree.insert(key);
    cout << "Insertion complete." << endl;
}

void del()
{
    cout << "||| Deletion Operation |||" << endl;
    DATA_TYPE key = get_key<DATA_TYPE>("Enter value to delete: ");
    int completion_code = rbtree.remove(key);
    if (completion_code == 0)
    { 
        cout << "Succesfully deleted node with value: " << key << endl;
    }
    else
    {
        cout << "Node with value: " << key << " wasn't found in the tree" << endl;
    }
    cout << "Deletion complete." << endl;
}
void search() 
{
    cout << "||| Search Operation |||" << endl;
    DATA_TYPE key = get_key<DATA_TYPE>("Enter value to find: ");
    bool success_code = rbtree.search_success(key);
    if (success_code == 1)
    { 
        cout << "Succesfully found node in a tree" << endl;
    }
    else
    {
        cout << "Node with value: " << key << " wasn't found in the tree" << endl;
    } 
}


void display_as_tree()
{
    cout << "Displaying Red-Black-Tree: ";
    rbtree.print2D();
}

void in_order_print() 
{
    cout << "In-Order Print: ";
    rbtree.printInOrder();
}

void level_order_print() 
{
    cout << "Level-Order Print: ";
    rbtree.printLevelOrder();
}
void sum_of_all_leaf_nodes() 
{
    cout << "Sum of all leaf nodes = " << rbtree.findLeafSum();
}
void print_tree_height() 
{
    cout << "Tree Height = " << rbtree.findHeight();
}

// Driver program to test Red-Black Tree
int main()
{
    // Printing Red-Black Tree
    add_initial_nodes();
    cout << "Initial Red-Black Tree created." << endl;
    int cmd;
    while (true)
    {
        while (true)
        {
            cout << "\n\n\t-- Enter Your Command Code --" << endl;
            cout << "1: Insert" << endl;
            cout << "2: Delete" << endl;
            cout << "3: Search" << endl;
            cout << "4: Display as a tree" << endl;
            cout << "5: In-Order print" << endl;
            cout << "6: Level-Order print" << endl;
            cout << "7: Sum of all leaf nodes" << endl;
            cout << "8: Print Tree Height" << endl;
            cout << "0: Exit" << endl;
            cout << "\tCommand Code: ";
            if (cin >> cmd && cmd >= 0 && cmd <= 8) break;
            clear_cin();
            cout << "Invalid Command Code\n";
        }

        cout << endl;
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
                display_as_tree();
                break;
            case 5:
                in_order_print();
                break;
            case 6:
                level_order_print();
                break;
            case 7:
                sum_of_all_leaf_nodes();
                break;
            case 8:
                print_tree_height();
                break;
        }
    }


    return 0;
}