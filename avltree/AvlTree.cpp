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

void AvlTree::insert(const int value) {
    if (!search(value)) {
        if (root == nullptr) {
            root = new Node(value);

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
                root->updateBalances();
            }
        }
    }
}


void AvlTree::Node::insert(const int value) {
    if (this->value > value) {
        if (this->left != nullptr) {
            this->left->insert(value);
        } else {
            this->left = new Node(value, this);
        }
        this->parent->updateBalances();
        upIn(this->parent);
    } else {
        if (this->right != nullptr) {
            this->right->insert(value);
        } else {
            this->right = new Node(value, this);
            this->parent->updateBalances();
            upIn(this->right);
        }
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
                // Set the ro ot pointer to symSucc
                root = symSucc;
                root->updateBalances();
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
            upOut(parent);
        } else if (right == nullptr && !isLeaf()) {
            if (this->value == parent->left->value) {
                parent->left = left;
            } else {
                parent->right = left;
            }
            parent->updateBalances();
            upOut(parent);

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
            if (parent->left->value == value) {
                parent->left = symSucc;
            } else {
                parent->right = symSucc;
            }
            // Call lasRight Again
            symSucc->updateBalances();
            upOut(symSucc);
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

bool AvlTree::Node::isLeaf() {
    return left == nullptr && right == nullptr;
}

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
        this->balance = -this->left->updateBalances() + 1;
    } else {
        this->balance = (this->right->updateBalances() + 1) - (this->left->updateBalances() + 1);
    }
    return this->balance;
}


void AvlTree::Node::upIn(Node *p) {
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
                parent->balance = -1;
                upIn(parent);
            }
            //case 1.3
            else if (parent->balance == -1) {
                //case 1.3.1
                if (p->balance == -1) {
                    rotateRight(parent);
                }
                //case 1.3.2
                else {
                    rotateLeft(p);
                    rotateRight(parent);
                }
            }
        }
        //the node to add is on the right side
        else {
            //case 1.3
            if (parent->balance == 1) {
                //case 1.3.1
                if (p->balance == 1) {
                    rotateLeft(parent);
                }
                    //case 1.3.2
                else {
                    rotateRight(p);
                    rotateLeft(parent);
                }
            }
            //case 1.2
            else if(parent->balance == 0) {
                parent->balance == 1;
                upIn(parent);
            }
            //case 1.1
            else if (parent->balance == -1) {
                parent->balance = 0;
            }
        }
    }
}

void AvlTree::Node::upOut(Node *p) {

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
                parent->balance == 1;
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
                if (p->balance == 0)  {
                    rotateRight(parent);
                }
                //case 1.3.2
                else if(p->balance == 1) {
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

AvlTree::Node * AvlTree::Node::rotateRight(Node *p) {
    auto *parent = p->parent;
    auto *rightNodeTail = p->right;
    auto *leftNodeTail = p->left;
    auto *rightParentTail = parent->right;

    if (parent->parent->left == parent) {
        parent->parent->left = p;
    } else {
        parent->parent->right = p;
    }
    p->left = leftNodeTail;
    p->right = parent;
    p->right->left = rightNodeTail;
    p->right->right = rightParentTail;

    //p->updateBalances();
    return p->left;

}

AvlTree::Node * AvlTree::Node::rotateLeft(Node *p) {
    auto *parent = p->parent;
    auto *leftTail = p->left;
    auto *rightTail = p->right;

    if (parent->left == p) {
        parent->left = rightTail;
    } else {
        parent->right = rightTail;
    }
    p->right = rightTail->left;
    rightTail->left = p;

    //p->updateBalances();
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

