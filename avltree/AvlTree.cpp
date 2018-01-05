#include "AvlTree.h"
#include <functional>

using namespace ::std;

/********************************************************************
 * Search
 *******************************************************************/

/**
 * Searches for a value in the Tree.
 * @param value value to look for
 * @return true if found, false otherwise.
 * @related searchNode
 */
bool AvlTree::search(const int value) const {
    if (root != nullptr) {
        if (root->value == value) {
            return true;
        } else {
            // If our value is bigger than the search value, we look left
            if (root->value > value) {
                if (root->left != nullptr) {
                    return root->left->search(value) != nullptr;
                } else {
                    return false;
                }
            } else {
                // Otherwise, we look right
                if (root->right != nullptr) {
                    return root->right->search(value) != nullptr;
                } else {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
}

/**
 * Searches for a value in the Tree. Node function.
 * @param value Value to search for.
 * @return Node pointer if found, nullpointer otherwise.
 */
AvlTree::Node *AvlTree::Node::search(const int value) {
    if (this->value != value) {
        if (this->value > value) {
            if (this->left != nullptr) {
                return this->left->search(value);
            } else {
                return nullptr;
            }
        } else {
            if (this->right != nullptr) {
                return this->right->search(value);
            } else {
                return nullptr;
            }
        }
    } else {
        return this;
    }
}

/********************************************************************
 * Insert
 *******************************************************************/

/**
 * Insert a value to the tree, if it isn't already contained.
 * @param value [in] value to insert.
 */
void AvlTree::insert(const int value) {
    if (!search(value)) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            if (root->value > value) {
                if (root->left != nullptr) {
                    root->left->insert(value);
                } else {
                    root->left = new Node(value);
                }
            } else {
                if (root->right != nullptr) {
                    root->right->insert(value);
                } else {
                    root->right = new Node(value);
                }
            }
        }
    }
}

/**
 * Inserts a value in the Tree. Node fuction to prevent multiple sub-functions.
 * @param value [in] Value to insert
 */
void AvlTree::Node::insert(const int value) {
    if (this->value > value) {
        if (this->left != nullptr) {
            this->left->insert(value);
        } else {
            this->left = new Node(value);
        }
    } else {
        if (this->right != nullptr) {
            this->right->insert(value);
        } else {
            this->right = new Node(value);
        }
    }
}


/********************************************************************
 * Remove
 *******************************************************************/

/**
 * Remove a value if it is in the tree
 * @param value value to remove
 */
void AvlTree::remove(const int value) {
    if (search(value)) {

    }
}

/********************************************************************
 * Utils
 *******************************************************************/

/**
 * Checks if a Node is a Leaf
 * @return true if it is a leaf, false otherwise.
 */
bool AvlTree::Node::isLeaf() {
    return left == nullptr && right == nullptr;
}

/**
 * Search the Node for a value.
 * @param value value to search for.
 * @return pointer if found, nullptr otherwise.
 * @relates search
 */
AvlTree::Node *AvlTree::searchNode(const int value) {
    if (root->value == value) {
        return root;
    } else {
        if (root->value > value) {
            if (root->left != nullptr) {
                return root->left->search(value);
            } else {
                return nullptr;
            }
        } else {
            if (root->right != nullptr) {
                return root->right->search(value);
            } else {
                return nullptr;
            }
        }
    }
}


/********************************************************************
 * Rotations
 *******************************************************************/

void AvlTree::updateBalances() {

}




/********************************************************************
 * Destructors
 *******************************************************************/

/**
 * Destructor for Node, deletes all the childs.
 */
AvlTree::Node::~Node() {
    delete left;
    delete right;
}

/**
 * Destructor for Tree, deletes Root-Node
 */
AvlTree::~AvlTree() {
    delete root;
}


/********************************************************************
 * Constructors
 *******************************************************************/

/**
 * Construct a new Node with no child nodes.
 * @param value Value of the Node
 */
AvlTree::Node::Node(const int value) : value(value) {

}

/**
 * Constructs a new Node with the given child nodes.
 * @param value Value of the Node.
 * @param left  Left child Node.
 * @param right Right child Node.
 */
AvlTree::Node::Node(const int value, AvlTree::Node *left, AvlTree::Node *right) : value(value), left(left),
                                                                                  right(right) {

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

/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &os, const int value, const AvlTree::Node *node, const string l)> printToOs
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

