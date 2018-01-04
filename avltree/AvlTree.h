#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AvlTree {

private:

    struct Node {
        const int value;
        Node *left = nullptr;
        Node *right = nullptr;

        explicit Node(const int value);
        Node(const int value, Node* left, Node* right);
        ~Node();
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;
    Node* searchLeft(const int value, Node* node)const;
    Node* searchRight(const int value, Node* node) const;
    Node* searchNode(const int value);
    bool isLeaf();

public:

    ~AvlTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //TREES_AVLTREE_H
