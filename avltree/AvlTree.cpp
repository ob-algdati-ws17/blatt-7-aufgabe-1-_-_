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
            root->updateBalances();
        } else {
            if (root->value > value) {
                if (root->left != nullptr) {
                    root->left->insert(value);
                } else {
                    root->left = new Node(value, root);
                }
            } else {
                if (root->right != nullptr) {
                    root->right->insert(value);
                } else {
                    root->right = new Node(value, root);
                }
                root->right->updateBalances();
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
            this->left = new Node(value, this);
        }
        this->updateBalances();
    } else {
        if (this->right != nullptr) {
            this->right->insert(value);
        } else {
            this->right = new Node(value, this);
            this->updateBalances();
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
        if (root->value == value) {
            if (root->isLeaf()) {
                root = nullptr;
                // Root either has no left or right children. Easiest case.
            } else if (root->right == nullptr) {
                root = root->left;
            } else if (root->left == nullptr) {
                root = root->right;
            } else {
                auto symSucc = root->findSymS(root);
                auto lastRight = symSucc->lastRight();
                // If symSucc has children, we want to put them in front of ours.
                if (lastRight != nullptr) {
                    lastRight->right = root->right;
                    root->right->parent = lastRight;
                }
                // Set the new left side of symSucc
                symSucc->left = root->left;
                // Keep the parents correct
                root->left->parent = symSucc;
                // symSucc will be the new root, so no parent
                symSucc->parent = nullptr;
                // Set the ro ot pointer to symSucc
                root = symSucc;
                root->lastRight()->updateBalances();
            }
        } else {
            root->remove(value);
        }
    }
}

void AvlTree::Node::remove(const int value) {
    if (value == this->value) {
        if (left == nullptr && !isLeaf()) {
            // Getting our position with the parent
            if (this->value == parent->right->value) {
                parent->right = right;
            } else {
                parent->left = right;
            }
            parent->updateBalances();
        } else if (right == nullptr && !isLeaf()) {
            if (this->value == parent->left->value) {
                parent->left = left;
            } else {
                parent->right = left;
            }
            parent->updateBalances();
        } else {
            auto symSucc = findSymS(this);
            auto lastRight = symSucc->lastRight();
            // If SymSucc has right children, put them before ours.
            if (lastRight != nullptr) {
                lastRight->right = this->right;
                this->right->parent = lastRight;
            }
            // Set the new left side of symSucc
            symSucc->left = this->left;
            // Keep the parents correct
            this->left->parent = symSucc;
            symSucc->parent = this->parent;
            if (parent->left->value ==  value) {
                parent->left = symSucc;
            } else {
                parent->right = symSucc;
            }
            // Call lasRight Again
            symSucc->lastRight()->updateBalances();
        }
        this->left = nullptr;
        this->right = nullptr;
        delete this;
        return;
    } else if (this->value > value) {
        this->left->remove(value);
    } else {
        this->right->remove(value);
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

AvlTree::Node *AvlTree::Node::lastRight() {
    auto lastRight = this;
    if (lastRight->right != nullptr) {
        while (lastRight->right != nullptr)
            lastRight = lastRight->right;
    }
    if (lastRight == this) {
        return nullptr;
    }
    return lastRight;
}


/**
 * Finds the symmetric successor for a node. Moved to Node struct to have accessability from Node remove.
 * @param node Node to find successor for.
 * @return Successor node if found, nullpointer otherwise.
 */
AvlTree::Node *AvlTree::Node::findSymS(Node* node) {
    auto result = node->right;
    if (result == nullptr)
        return result;
    while (result->left != nullptr) {
        result = result->left;
    }
    return result;
}

/********************************************************************
 * Rotations
 *******************************************************************/

void AvlTree::Node::updateBalances() {

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


AvlTree::Node::Node(const int value, AvlTree::Node *parent) : value(value), parent(parent) {

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
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs
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

