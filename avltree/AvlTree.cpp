#include "AvlTree.h"
#include <functional>

using namespace ::std;

/********************************************************************
 * Search
 *******************************************************************/

bool AvlTree::search(const int value) const {
    if (root != nullptr) {
        if (root->value == value) {
            return true;
        } else {
            // If our value is bigger than the search value, we look left
            if (root->value > value) {
                if (root->left != nullptr) {
                    return search(value, root->left) != nullptr;
                } else {
                    return false;
                }
            } else {
                // Otherwise, we look right
                if (root->right != nullptr) {
                    return search(value, root->right) != nullptr;
                } else {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
}

AvlTree::Node * AvlTree::search(const int value, Node* node)const {
    if (node->value != value) {
        if (node->value > value) {
            if (node->left != nullptr) {
                return search(value, node->left);
            } else {
                return nullptr;
            }
        } else {
            if (node->right != nullptr) {
                return search(value, node->right);
            } else {
                return nullptr;
            }
        }
    } else {
        return node;
    }
}

/********************************************************************
 * Insert
 *******************************************************************/

void AvlTree::insert(const int value) {
    if (!search(value)) {
        if (root == nullptr) {
            root = new Node(value);

        } else {
            if (root->value > value) {
                if (root->left != nullptr) {
                    insert(value, root->left);
                } else {
                    root->left = new Node(value, root);
                    root->updateBalances();
                }

            } else {
                if (root->right != nullptr) {
                   insert(value, root->right);
                } else {
                    root->right = new Node(value, root);
                    root->updateBalances();
                }

            }
        }
    }
}


void AvlTree::insert(const int value, Node* node) {
    if (node->value > value) {
        if (node->left != nullptr) {
            insert(value, node->left);
        } else {
            node->left = new Node(value, node);
        }
        node->updateBalances();
        upIn(node);
    } else {
        if (node->right != nullptr) {
            insert(value, node->right);
        } else {
            node->right = new Node(value, node);
        }
        node->updateBalances();
        upIn(node);
    }
}


/********************************************************************
 * Remove
 *******************************************************************/

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
                // Set the root pointer to symSucc
                root = symSucc;
                root->updateBalances();
            }
        } else {
            remove(value, root);
        }
    }
}

void AvlTree::remove(const int value, Node* node) {
    if (value == node->value) {
        if (node->left == nullptr && node->right == nullptr) {
            if (node->value == node->parent->right->value) {
                node->parent->right = nullptr;
            } else {
                node->parent->left = nullptr;
            }
            node->parent->updateBalances();
            upOut(node->parent);
            delete node;
            return;
        } else if (node->left == nullptr && !node->isLeaf()) {
            // Getting our position with the parent
            if (node->value == node->parent->right->value) {
                node->parent->right = node->right;
            } else {
                node->parent->left = node->right;
            }
            node->parent->updateBalances();
            upOut(node->parent);
            delete node;
            return;
        } else if (node->right == nullptr && !node->isLeaf()) {
            if (node->value == node->parent->left->value) {
                node->parent->left = node->left;
            } else {
                node->parent->right = node->left;
            }
            node->parent->updateBalances();
            upOut(node->parent);
            delete node;
            return;
        } else {
            auto symSucc = node->findSymS(node);
            auto lastRight = symSucc->lastRight();
            // If SymSucc has right children, put them before ours.
            if (lastRight != nullptr) {
                lastRight->right = node->right;
                node->right->parent = lastRight;
            }
            // Set the new left side of symSucc
            symSucc->left = node->left;
            // Keep the parents correct
            node->left->parent = symSucc;
            symSucc->parent = node->parent;
            if (node->parent->left->value == value) {
                node->parent->left = symSucc;
            } else {
                node->parent->right = symSucc;
            }
            // Call lasRight Again
            symSucc->updateBalances();
            upOut(symSucc);
        }
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        return;
    } else if (node->value > value) {
        remove(value, node->left);
    } else {
        remove(value, node->right);
    }
}

/********************************************************************
 * Utils
 *******************************************************************/

bool AvlTree::Node::isLeaf() {
    return left == nullptr && right == nullptr;
}

AvlTree::Node *AvlTree::searchNode(const int value) {
    if (root->value == value) {
        return root;
    } else {
        if (root->value > value) {
            if (root->left != nullptr) {
                return search(value, root->left);
            } else {
                return nullptr;
            }
        } else {
            if (root->right != nullptr) {
                return search(value, root->right);
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

AvlTree::Node *AvlTree::Node::findSymS(Node *node) {
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

bool AvlTree::isEquallyBalanced() const {
    return root->balance == 0;
}

int AvlTree::Node::updateBalances() {
    if (this->left == nullptr && this->right == nullptr) {
        this->balance = 0;
    } else if (this->left == nullptr && this->right != nullptr) {
        this->balance = this->right->updateBalances() + 1;
    } else if (this->right == nullptr && this->left != nullptr) {
        this->balance = 0 - (this->left->updateBalances() + 1);
    } else {
        this->balance = (this->right->updateBalances()) - (this->left->updateBalances());
    }
    return this->balance;
}


void AvlTree::upIn(Node *p) {
    if (p != nullptr && p->parent != nullptr) {

        auto *parent = p->parent;
        //the node to add is on the left side
        if (parent->left == p) {
            //case 1.1
            if (parent->balance == 1) {
                parent->balance = 0;
            }
                //case 1.2
            else if (parent->balance == 0) {
                parent->updateBalances();
                //parent->balance = -1;
                upIn(p->parent);
            }
                //case 1.3
            else if (parent->balance == -1) {
                //case 1.3.1
                if (p->balance == -1) {
                    rotateRight(p);
                    p->updateBalances();
                }
                    //case 1.3.2
                else {
                    rotateLeft(p->right);
                    rotateRight(p->parent);
                    p->parent->updateBalances();
                }
            }
        }
            //the node to add is on the right side
        else {
            //case 1.3
            if (parent->balance == 1) {
                //case 1.3.1
                if (p->balance == 1) {
                    rotateLeft(p);
                    p->updateBalances();
                }
                    //case 1.3.2
                else {
                    rotateRight(p->left);
                    rotateLeft(p->parent);
                    p->parent->updateBalances();
                }
            }
                //case 1.2
            else if (parent->balance == 0) {
                parent->updateBalances();
                //parent->balance = 1;
                upIn(p->parent);
            }
                //case 1.1
            else if (parent->balance == -1) {
                parent->balance = 0;
            }
        }
    }
}

void AvlTree::upOut(AvlTree::Node *p) {

    if (p != nullptr && p->parent != nullptr) {
        auto *parent = p->parent;
        //the node to delete is on the left side
        if (parent->left == p) {
            //case 1.1
            if (parent->balance == -1) {
                parent->balance = 0;
                upOut(parent);
            }
                //case 1.2
            else if (parent->balance == 0) {
                parent->balance = 1;
            }
                //case 1.3
            else if (parent->balance == 1) {
                //case 1.3.1
                if (p->balance == 0) {
                    rotateLeft(parent);
                }
                    //case 1.3.2
                else if (p->balance == 1) {
                    parent = rotateLeft(parent);
                    upOut(parent);
                }
                    //case 1.3.3
                else if (p->balance == -1) {
                    rotateRight(parent->right);
                    parent = rotateLeft(parent);
                    upOut(parent);
                }
            }
        }
            //the node to delete is on the right side
        else if (parent->right = p) {
            //case 1.3
            if (parent->balance == -1) {
                //case 1.3.1
                if (p->balance == 0) {
                    rotateRight(parent);
                }
                    //case 1.3.2
                else if (p->balance == 1) {
                    parent = rotateRight(parent);
                    upOut(parent);
                }
                    //case 1.3.3
                else if (p->balance == -1) {
                    rotateLeft(parent->left);
                    parent = rotateRight(parent);
                    upOut(parent);
                }
            }
                //case 1.2
            else if (parent->balance == 0) {
                parent->balance = -1;
            }
                //case 1.1
            else if (parent->balance == 1) {
                parent->balance = 0;
                upOut(parent);
            }

        }
    }

}

AvlTree::Node *AvlTree::rotateRight(Node *p) {
    auto *parent = p->parent;
    auto *rightNodeTail = p->right;
    auto *leftNodeTail = p->left;
    auto *rightParentTail = parent->right;
    auto *newParent = parent->parent;


    if (parent->left == p) {
        parent->left = p;
    } else {
        parent->right = p;
    }
    p->left = leftNodeTail;
    p->right = parent;
    p->right->parent = p;
    p->right->left = rightNodeTail;
    p->right->right = rightParentTail;
    p->parent = newParent;

    if (p->parent == nullptr) {
        root = p;
    }

    //p->updateBalances();
    return p->left;

}

AvlTree::Node *AvlTree::rotateLeft(Node *p) {
    auto *parent = p->parent;
    auto *rightNodeTail = p->right;
    auto *leftNodeTail = p->left;
    auto *leftParentTail = parent->left;
    auto *newParent = parent->parent;

    if (parent->right == p) {
        parent->right = p;
    } else {
        parent->left = p;
    }

    p->right = rightNodeTail;
    p->left = parent;
    p->left->parent = p;
    p->left->left = leftParentTail;
    p->left->right = leftNodeTail;

    p->parent = newParent;
    if (p->parent == nullptr) {
        root = p;
    }
    p->updateBalances();
    return parent->right;
}

/********************************************************************
 * Destructors
 *******************************************************************/

AvlTree::Node::~Node() {
    delete left;
    delete right;
}

AvlTree::~AvlTree() {
    delete root;
}


/********************************************************************
 * Constructors
 *******************************************************************/

AvlTree::Node::Node(const int value) : value(value) {

}

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

