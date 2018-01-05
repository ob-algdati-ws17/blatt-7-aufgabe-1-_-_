#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AvlTree {

private:

    struct Node {
        //! Simple constructor, left and right are null.
        explicit Node(const int value);
        //! Constructor with value and parent.
        Node(const int value, Node* parent);
        //! More complex constructor with initialisation for left and right.
        Node(const int value, Node* left, Node* right);
        ~Node();

        const int value;        //!< Value of the node
        Node *left = nullptr;   //!< Left child
        Node *right = nullptr;  //!< Right child
        Node *parent = nullptr; //!< Parent node
        int balance = 0; //!< Current balance of the Node

        void insert(const int value);   //!< To remove the need for multiple sub-functions
        Node* search(const int value);  //!< To remove the need for multiple sub-functions
        void remove(const int value);   //!< To remove the need for multiple sub-functions
        Node* findSymS(Node* node);     //!< Finds the symmetric Successor
        bool isLeaf();

        vector<int> *preorder() const;  //!< Hauptreihenfolge
        vector<int> *inorder() const;   //!< Symmetrische Reihenfolge
        vector<int> *postorder() const; //!< Nebenreihenfolge
    };

    //! Root node for the Tree
    Node *root = nullptr;
    Node* searchNode(const int value);
    void updateBalances();


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
