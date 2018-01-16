#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * Class for a balanced Tree
 */
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
        * Makes left/right rotations depending on the balances of the nodes (insert)
        * @param p left or right node
        */
        void upIn(Node *p);


        /**
         * Makes left/right rotations depending on the balances of the nodes (delete)
         * @param p left or right node
         */
        void upOut(Node *p);

        /**
         * Rotates Left
         * @param p the node to be rotated around
         * @return the node, which is now on top
         */
        Node *rotateLeft(Node *p);

        /**
         * Rotates right
         * @param p the node to be rotated around
         * @return the node, which is now on top
         */
        Node *rotateRight(Node *p);

        /**
        * Finds the symmetric successor for a node. Moved to Node struct to have accessability from Node remove.
        * @param node Node to find successor for.
        * @return Successor node if found, nullpointer otherwise.
        */
        Node *findSymS(Node *node);

        /**
        * Checks if a Node is a Leaf
        * @return true if it is a leaf, false otherwise.
        */
        bool isLeaf();

        /**
         * Updates the balances for this Node. Returns current balance.
         * @return this->balance
         */
        int updateBalances();


        /**
         * Finds the last right child of this Node.
         * @return The last right node.
         */
        Node *lastRight();

        /**
         * Gets the Node and its Children in Preorder.
         * @return Vector with the Nodes in Order.
         */
        vector<int> *preorder() const;

        /**
         * Gets the Node and its Children in order.
         * @return Vector with the Nodes in Order.
         */
        vector<int> *inorder() const;

        /**
         * Gets the Node and its Children in Postorder.
         * @return Vector with the Nodes in Order.
         */
        vector<int> *postorder() const;
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

    /**
     * Sets the root Node.
     * @param node New root.
     */
    void setRoot(Node * node);


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

     /**
     * checks, if the root is balanced
     * @return true, if the balance of the root is 0
     */
    bool isEquallyBalanced() const;

    /**
    * Gets the Tree in Preorder.
    * @return Vector with the Nodes in Order.
    */
    vector<int> *preorder() const;  // (Hauptreihenfolge)
    /**
    * Gets the Tree in Symmetrical Order.
    * @return Vector with the Nodes in Order.
    */
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    /**
    * Gets the Tree in Postorder.
    * @return Vector with the Nodes in Order.
    */
    vector<int> *postorder() const; // (Nebenreihenfolge)

    /**
     * Prints the Tree to the output stream.
     * @return
     */
    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //TREES_AVLTREE_H
