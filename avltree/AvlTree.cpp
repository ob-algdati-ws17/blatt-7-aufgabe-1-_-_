#include "AvlTree.h"
#include <functional>

using namespace ::std;

/********************************************************************
 * Search
 *******************************************************************/

bool AvlTree::search(const int value) const {
    if (root->value != value) {
        if (!searchInPartTree(value, root->left)) {
            if (!searchInPartTree(value, root->left)) {
                return false;
            }
        }
    }
    return true;
}

bool AvlTree::searchInPartTree(const int value, AvlTree::Node *node)const {
    if (node != nullptr) {
        if (node->value != value) {
            if (!searchInPartTree(value, node->left)) {
                if (!searchInPartTree(value, node->right)) {
                    return false;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}
/********************************************************************
 * Insert
 *******************************************************************/

void AvlTree::insert(const int value) {
    if (!search(value)) {

    }
}

/********************************************************************
 * Remove
 *******************************************************************/

void AvlTree::remove(const int value) {

}

/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AvlTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(value);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AvlTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(value);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AvlTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(value);
    return vec;
}

/**
 * Construct a new Node with no child nodes.
 * @param value Value of the Node
 * @param parent Parent Node, can be null if its the root.
 */
AvlTree::Node::Node(const int value, AvlTree::Node *parent) : value(value), parent(parent) {

}

/**
 * Constructs a new Node with the given child nodes.
 * @param value Value of the Node.
 * @param left  Left child Node.
 * @param right Right child Node.
 */
AvlTree::Node::Node(const int value, AvlTree::Node *left, AvlTree::Node *, AvlTree::Node *right) : value(value),
                                                                                                 parent(parent),
                                                                                                 left(left),
                                                                                                 right(right) {

}


/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int value, const AvlTree::Node* node, const string l)> printToOs
            = [&](std::ostream &os, const int value, const AvlTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->value
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->value, node->left, "l");
                    printToOs(os, node->value, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->value, tree.root->left, "l");
        printToOs(os, tree.root->value, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}

/**
 * Destructor for Node, deletes all the childs.
 */
AvlTree::Node::~Node() {
    if (left != nullptr) {
        delete nullptr;
    }
    if (right != nullptr) {
        delete nullptr;
    }
}

/**
 * Destructor for Tree, deletes Root-Node
 */
AvlTree::~AvlTree() {
    delete root;
}


