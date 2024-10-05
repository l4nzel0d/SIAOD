#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Enumeration for colors of nodes in Red-Black Tree
enum Color { RED, BLACK };

// Class template for Red-Black Tree
template <typename T>
class RedBlackTree {
private:
    // Structure for a node in Red-Black Tree
    struct Node {
        T data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;

        // Constructor to initialize node with data and color
        Node(T value);
    };

    Node* root; // Root of the Red-Black Tree

    // Utility functions
    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void fixInsert(Node*& node);
    void fixDelete(Node*& node);
    Node* minValueNode(Node*& node);
    void transplant(Node*& root, Node*& u, Node*& v);
    void printHelper(Node* root, string indent, bool last);
    void deleteTree(Node* node);
    string nodeToString(Node* node);
    void printInOrder(Node* node);
    void printLevelOrder(Node* node);
    int findHeight(Node* node);
    int findLeafSum(Node* node);
    bool isLeafNode(Node* node);
    void print2DUtil(Node* root, int space);
    Node* search(T key);

public:
    // Constructor and Destructor
    RedBlackTree();
    ~RedBlackTree();

    // Public member functions
    void insert(T key);
    int remove(T key);
    bool search_success(T key);
    void printTree();
    void print2D();
    void printInOrder();
    void printLevelOrder();
    int findHeight();
    int findLeafSum();
};

#include "RBTree.cpp" // Include implementation file

#endif // RBTREE_H
