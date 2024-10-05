#include "RBTree.h"

// Node constructor
template <typename T>
RedBlackTree<T>::Node::Node(T value)
    : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}

// Constructor: Initialize Red-Black Tree
template <typename T>
RedBlackTree<T>::RedBlackTree() : root(nullptr) {}

// Destructor: Delete Red-Black Tree
template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    deleteTree(root);
}

// Utility function: Left Rotation
template <typename T>
void RedBlackTree<T>::rotateLeft(Node*& node) {
    Node* child = node->right;
    node->right = child->left;
    if (node->right != nullptr)
        node->right->parent = node;
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->left = node;
    node->parent = child;
}

// Utility function: Right Rotation
template <typename T>
void RedBlackTree<T>::rotateRight(Node*& node) {
    Node* child = node->left;
    node->left = child->right;
    if (node->left != nullptr)
        node->left->parent = node;
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->right = node;
    node->parent = child;
}

// Utility function: Fixing Insertion Violation
template <typename T>
void RedBlackTree<T>::fixInsert(Node*& node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;
    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

// Utility function: Fixing Deletion Violation
template <typename T>
void RedBlackTree<T>::fixDelete(Node*& node) {
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            Node* sibling = node->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->right != nullptr)
                    sibling->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            Node* sibling = node->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = node->parent;
            } else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling->left != nullptr)
                    sibling->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}

// Utility function: Find Node with Minimum Value
template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::minValueNode(Node*& node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Utility function: Transplant nodes in Red-Black Tree
template <typename T>
void RedBlackTree<T>::transplant(Node*& root, Node*& u, Node*& v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

// Utility function: Helper to print Red-Black Tree
template <typename T>
void RedBlackTree<T>::printHelper(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        string sColor = (root->color == RED) ? "RED" : "BLACK";
        cout << root->data << "(" << sColor << ")" << endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

// Utility function: Delete all nodes in the Red-Black Tree
template <typename T>
void RedBlackTree<T>::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Public function: Insert a new key into the Red-Black Tree
template <typename T>
void RedBlackTree<T>::insert(T key) {
    Node* newNode = new Node(key);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (newNode->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    newNode->parent = y;
    if (y == nullptr)
        root = newNode;
    else if (newNode->data < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    fixInsert(newNode);
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::search(T key)
{
    Node* current = root;
    while (current != nullptr)
    {
        if (key < current->data)
            current = current->left;
        else if (key > current->data)
            current = current->right;
        else
            break;
    }
    return current; 
}

template <typename T>
bool RedBlackTree<T>::search_success(T key)
{
    return search(key) != nullptr;
}

// Public function: Remove a key from the Red-Black Tree
template <typename T>
int RedBlackTree<T>::remove(T key) 
{
    Node* node = root;
    Node* z = nullptr;
    Node* x = nullptr;
    Node* y = nullptr;
    while (node != nullptr) {
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }

    if (z == nullptr) {
        cout << "Key not found in the tree" << endl;
        return 1;
    }

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = minValueNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y;
        }
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK) {
        fixDelete(x);
    }
    return 0;
}


template<typename T>
string RedBlackTree<T>::nodeToString(Node* node)
{
    if (node == nullptr)
    {
        return "NULL";
    }

    string color = (node->color == RED) ? "R" : "B";
    string output = to_string(node->data) + "-" + color;
    return output;    
}

// Public function: Print the Red-Black Tree
template <typename T>
void RedBlackTree<T>::printTree() {
    printHelper(root, "", true);
}

// Public function: Print 2D representation of the Red-Black Tree
template <typename T>
void RedBlackTree<T>::print2D() {
    if (root == nullptr) cout << "Tree is empty." << endl;
    print2DUtil(root, 0);
}

int const COUNT = 10;

template <typename T>
void RedBlackTree<T>::print2DUtil(Node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << nodeToString(root) << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Public function: Print nodes in In-Order
template <typename T>
void RedBlackTree<T>::printInOrder() {
    printInOrder(root);
}

// Utility function: Helper for In-Order Traversal
template <typename T>
void RedBlackTree<T>::printInOrder(Node* node) {
    if (node != nullptr) {
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
}

// Public function: Print nodes in Level Order
template <typename T>
void RedBlackTree<T>::printLevelOrder() {
    printLevelOrder(root);
}

// Utility function: Helper for Level Order Traversal
template <typename T>
void RedBlackTree<T>::printLevelOrder(Node* node) {
    if (node == nullptr) return;
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node* temp = q.front();
        cout << temp->data << " ";
        q.pop();
        if (temp->left != nullptr) q.push(temp->left);
        if (temp->right != nullptr) q.push(temp->right);
    }
}

// Public function: Find height of the tree
template <typename T>
int RedBlackTree<T>::findHeight() {
    return findHeight(root);
}

// Utility function: Helper for height calculation
template <typename T>
int RedBlackTree<T>::findHeight(Node* node) {
    if (node == nullptr) return 0;
    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
}

// Public function: Find sum of all leaf nodes
template <typename T>
int RedBlackTree<T>::findLeafSum() {
    return findLeafSum(root);
}

// Utility function: Helper for finding sum of leaf nodes
template <typename T>
int RedBlackTree<T>::findLeafSum(Node* node) {
    if (node == nullptr) return 0;
    if (isLeafNode(node)) return node->data;
    return findLeafSum(node->left) + findLeafSum(node->right);
}

// Utility function: Check if a node is a leaf node
template <typename T>
bool RedBlackTree<T>::isLeafNode(Node* node) {
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}
