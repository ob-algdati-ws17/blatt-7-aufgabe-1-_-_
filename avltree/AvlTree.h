#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AvlTree {

private:

    struct Node {
        /**
        * Construct a new Node with no child nodes.
        * @param value Value of the Node
        */
        explicit Node(const int value);

        /**
        * Constructs a new Node with the given child nodes.
        * @param value Value of the Node.
        * @param left  Left child Node.
        * @param right Right child Node.
        */
        Node(const int value, Node *parent);

        //! More complex constructor with initialisation for left and right.
        Node(const int value, Node *left, Node *right);

        /**
        * Destructor for Node, deletes all the childs.
        */
        ~Node();

        const int value;        //!< Value of the node
        Node *left = nullptr;   //!< Left child
        Node *right = nullptr;  //!< Right child
        Node *parent = nullptr; //!< Parent node
        int balance = 0; //!< Current balance of the Node

        /**
        * Inserts a value in the Tree. Node fuction to prevent multiple sub-functions.
        * @param value [in] Value to insert
        */
        void insert(const int value);

        /**
        * Searches for a value in the Tree. Node function.
        * @param value Value to search for.
        * @return Node pointer if found, nullpointer otherwise.
        */
        Node *search(const int value);

        /**
         * Removes a Value from the Tree. Node Function.
         * @param value Value to remove.
         */
        void remove(const int value);   //!< To remove the need for multiple sub-functions

        /**
        * Finds the symmetric successor for a node. Moved to Node struct to have accessability from Node remove.
        * @param node Node to find successor for.
        * @return Successor node if found, nullpointer otherwise.
        */
        Node *findSymS(Node *node);     //!< Finds the symmetric Successor

        /**
        * Checks if a Node is a Leaf
        * @return true if it is a leaf, false otherwise.
        */
        bool isLeaf();

        int updateBalances();

        Node *lastRight(); //!< Finds the last Right Child

        vector<int> *preorder() const;  //!< Hauptreihenfolge
        vector<int> *inorder() const;   //!< Symmetrische Reihenfolge
        vector<int> *postorder() const; //!< Nebenreihenfolge
    };

    //! Root node for the Tree
    Node *root = nullptr;

    /**
    * Search the Node for a value.
    * @param value value to search for.
    * @return pointer if found, nullptr otherwise.
    * @relates search
    */
    Node *searchNode(const int value);


public:

    /**
    * Destructor for Tree, deletes Root-Node
    */
    ~AvlTree();

    /**
    * Searches for a value in the Tree.
    * @param value value to look for
    * @return true if found, false otherwise.
    * @related searchNode
    */
    bool search(const int) const;

    /**
    * Insert a value to the tree, if it isn't already contained.
    * @param value [in] value to insert.
    */
    void insert(const int);

    /**
    * Remove a value if it is in the tree
    * @param value value to remove
    */
    void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //TREES_AVLTREE_H
