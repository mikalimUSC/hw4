#ifndef AVLBST_H
#define AVLBST_H


#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"
#include "print_bst.h"

struct KeyError {
};

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent);

    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance() const;

    void setBalance(int8_t balance);

    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value> *getParent() const override;

    virtual AVLNode<Key, Value> *getLeft() const override;

    virtual AVLNode<Key, Value> *getRight() const override;

protected:
    int8_t balance_; // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key,
    Value>::AVLNode(const Key &key, const Value &value, AVLNode<Key, Value> *parent) : Node<Key, Value>(
    key, value, parent), balance_(0) {
}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {
}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const {
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance) {
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff) {
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value> *>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value> *>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value> *>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    AVLTree();

    // void print() const;

    virtual void insert(const std::pair<const Key, Value> &new_item) override; // TODO
    virtual void remove(const Key &key) override; // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2);

    AVLNode<Key, Value> *predecessor(AVLNode<Key, Value> *current);

    AVLNode<Key, Value> *leftRotate(AVLNode<Key, Value> *x);

    AVLNode<Key, Value> *rightRotate(AVLNode<Key, Value> *y);

    void updateHeight(AVLNode<Key, Value> *node);

    // Add helper functions here
    void rebalance(AVLNode<Key, Value> *node);

    void removeHelper(const Key &key);

    virtual AVLNode<Key, Value> *getSmallestNode() const override;




    // AVLNode<Key, Value> *internalFind(const Key &key) const override;
    //
    // AVLNode<Key, Value> *internalFindHelper(AVLNode<Key, Value> *current, const Key &key) const;
};

template<class Key, class Value>
AVLTree<Key, Value>::AVLTree() {
}

// template<class Key, class Value>
// void AVLTree<Key, Value>::print() const {
//     // Cast root_ to Node* before passing to printRoot AUAGHH
//     this->printRoot(root_);
//     std::cout << "\n";
// }

// //
// template<typename Key, typename Value>
// AVLNode<Key, Value> *AVLTree<Key, Value>::internalFind(const Key &key) const {
//     //std::cout << "AVLTree internal find" << std::endl;
//     return dynamic_cast<AVLNode<Key, Value>*>(internalFindHelper(this->root_, key));
// }

// template<typename Key, typename Value>
// AVLNode<Key, Value> *AVLTree<Key, Value>::internalFindHelper(AVLNode<Key, Value> *current, const Key &key) const {
//     if (current == nullptr) {
//         return nullptr;
//     }
//
//     if (current->getKey() == key) {
//         return current;
//     }
//
//
//     AVLNode<Key, Value> *foundLeft = internalFindHelper(current->getLeft(), key);
//     if (foundLeft != nullptr) {
//         return foundLeft;
//     }
//
//     return internalFindHelper(current->getRight(), key);
// }


template<class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value> *x) {
    //std::cout << "Left rotating" << std::endl;
    AVLNode<Key, Value> *y = x->getRight();
    AVLNode<Key, Value> *T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);


    if (T2 != nullptr) {
        T2->setParent(x);
    }

    y->setParent(x->getParent());

    if (x == this->root_)
        this->root_ = y;
    else {
        if (x->getParent()->getLeft() == x)
            x->getParent()->setLeft(y);
        else
            x->getParent()->setRight(y);
    }
    x->setParent(y);
    x->setBalance((getSubtreeHeight(x->getLeft()) - getSubtreeHeight(x->getRight())));
    y->setBalance((getSubtreeHeight(y->getLeft()) - getSubtreeHeight(y->getRight())));

    //
    // std::cout << "After left rotating node " << y->getKey() << " has balance of " << static_cast<int>(y->getBalance()) << std::endl;
    // std::cout << "After left rotating node " << x->getKey() << " has balance of " << static_cast<int>(x->getBalance()) << std::endl;

    return y;
}

template<class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value> *y) {
    //  std::cout << "We in right rotate. Rotating " << y->getValue() <<  std::endl;
    AVLNode<Key, Value> *x = y->getLeft();
    AVLNode<Key, Value> *T2 = x->getRight();


    x->setRight(y);
    y->setLeft(T2);

    if (T2 != nullptr) {
        T2->setParent(y);
    }

    x->setParent(y->getParent());


    if (y == this->root_)
        this->root_ = x;
    else {
        if (y->getParent()->getLeft() == y) {
            y->getParent()->setLeft(x);
        } else {
            y->getParent()->setRight(x);
        }
    }
    y->setParent(x);


    //  std::cout << "x right is " << x->getRight()->getKey() << std::endl;
    y->setBalance((getSubtreeHeight(y->getLeft()) - getSubtreeHeight(y->getRight())));
    //  std::cout << "subtree height of x left "<< (getSubtreeHeight(x->getLeft())) << "subtree height of x right " << (getSubtreeHeight(x->getRight()))<<std::endl ;
    x->setBalance((getSubtreeHeight(x->getLeft()) - getSubtreeHeight(x->getRight())));

    // std::cout << "After right rotating node " << y->getKey() << " has balance of " << static_cast<int>(y->getBalance()) << std::endl;
    //  std::cout << "After right rotating node " << x->getKey() << " has balance of " << static_cast<int>(x->getBalance()) << std::endl;
    return x;
}

/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair) {
    AVLNode<Key, Value> *newNode = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    int8_t ogbalance = newNode->getBalance();
    // std::cout << "New node balance is " << static_cast<int>(newNode->getBalance()) << std::endl;
    if (this->root_ == nullptr) {
        this->root_ = newNode;
        //  std::cout << "Root is set to AVL newNode. Root balance is " << static_cast<int>(root_->getBalance()) << std::endl;
        newNode->setLeft(nullptr);
        newNode->setRight(nullptr);
        return;
    }


    AVLNode<Key, Value> *current = static_cast<AVLNode<Key, Value> *>(this->root_);

    while (true) {
        if (current->getKey() > newNode->getKey()) {
            if (current->getLeft() != nullptr) {
                current = static_cast<AVLNode<Key, Value> *>(current->getLeft());
            } else {
                current->setLeft(newNode);
                newNode->setParent(current);
                break;
            }
        } else if (current->getKey() < newNode->getKey()) {
            if (current->getRight() != nullptr) {
                current = static_cast<AVLNode<Key, Value> *>(current->getRight());
            } else {
                current->setRight(newNode);
                newNode->setParent(current);
                break;
            }
        } else {
            current->setValue(keyValuePair.second);
            delete newNode;
            return;
        }
    }


    // std::cout << "before rebalance " << newNode->getKey() << " has balance of " << static_cast<int>(newNode->getBalance()) << std::endl;
    //   std::cout << "before rebalance" << root_->getKey() << " has balance of " << static_cast<int>(root_->getBalance()) << std::endl;
    AVLNode<Key, Value> *parent = newNode->getParent();
    while (parent != nullptr) {
        if (newNode == parent->getLeft()) {
            parent->updateBalance(1);
        } else if (newNode == parent->getRight()) {
            parent->updateBalance(-1);
        }

        if (parent->getBalance() == 0) {
            break;
        } else if (parent->getBalance() == -2 || parent->getBalance() == 2) {
            //    std::cout << "rebalancing parent " << parent->getKey()<< "Because it's balance is "<< static_cast<int>(parent->getBalance()) << std::endl;
            rebalance(parent);
            break;
        }

        newNode = parent;
        parent = newNode->getParent();
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::rebalance(AVLNode<Key, Value> *node) {
    if (node->getBalance() == 2) {
       // std::cout << "Node balance: " << static_cast<int>(node->getBalance()) << std::endl;
        if (node->getLeft() != nullptr) {
            if (node->getLeft()->getBalance() >= 0) {
                rightRotate(node);
            } else {
                leftRotate(node->getLeft());
                rightRotate(node);
            }

        }else {
            leftRotate(node);
        }
        } else if (node->getBalance() == -2) {
        if (node->getRight() != nullptr) {
            if (node->getRight()->getBalance() <= 0) {
                leftRotate(node);
            } else {
                rightRotate(node->getRight());
                leftRotate(node);
            }
        }else {
            std::cout << "Right rotating " << node->getKey() << std::endl;
            rightRotate(node);
        }

    }
}


template<class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::getSmallestNode() const {
    // return BinarySearchTree<Key, Value>::getSmallestNode();
    AVLNode<Key, Value> *current = dynamic_cast<AVLNode<Key,Value>*>(this->root_);
    while (current != nullptr && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key &key) {
    removeHelper(key);


}



template<class Key, class Value>
void AVLTree<Key, Value>::removeHelper(const Key &key) {
    AVLNode<Key, Value> *nodeToRemove = dynamic_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    if (nodeToRemove == nullptr) {
        return;
    }

    // If node to remove has two children, swap it with its predecessor
    if (nodeToRemove->getLeft() != nullptr && nodeToRemove->getRight() != nullptr) {
        AVLNode<Key, Value> *predecessorNode = predecessor(nodeToRemove);
        nodeSwap(nodeToRemove, predecessorNode);
        if (nodeToRemove == dynamic_cast<AVLNode<Key,Value>*>(this->root_)){
            this->root_ = predecessorNode;
        }
        //nodeToRemove = predecessorNode;  // Now remove the predecessor (which has at most one child)
    }

    AVLNode<Key, Value> *parent = nodeToRemove->getParent();

    // Case 1:  no children (leaf node)
    if (nodeToRemove->getLeft() == nullptr && nodeToRemove->getRight() == nullptr) {
        if (parent == nullptr) { // Removing the root
            this->root_ = nullptr;
        } else if (parent->getLeft() == nodeToRemove) {
            parent->setLeft(nullptr);
        } else {
            parent->setRight(nullptr);
        }
    }

    // Case 2:  one child (left or right)
    else if (nodeToRemove->getLeft() == nullptr || nodeToRemove->getRight() == nullptr) {
        AVLNode<Key, Value> *child = (nodeToRemove->getLeft() != nullptr) ? nodeToRemove->getLeft() : nodeToRemove->getRight();

        if (parent == nullptr) { // Removing the root
            this->root_ = child;
        } else if (parent->getLeft() == nodeToRemove) {
            parent->setLeft(child);
        } else {
            parent->setRight(child);
        }

        child->setParent(parent);
    }


    delete nodeToRemove;


    AVLNode<Key, Value> *ancestor = parent;
    while (ancestor != nullptr) {

        int leftHeight = (ancestor->getLeft() != nullptr) ? getSubtreeHeight(ancestor->getLeft()) : 0;
        int rightHeight = (ancestor->getRight() != nullptr) ? getSubtreeHeight(ancestor->getRight()) : 0;

        ancestor->setBalance(rightHeight - leftHeight); // Update balance factor


        if (ancestor->getBalance() == 2 || ancestor->getBalance() == -2) {
            rebalance(ancestor);
            break;
        }

        ancestor = ancestor->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value> *n1, AVLNode<Key, Value> *n2) {
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    AVLNode<Key, Value>* n1p = n1->getParent();
    AVLNode<Key, Value>* n1r = n1->getRight();
    AVLNode<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    AVLNode<Key, Value>* n2p = n2->getParent();
    AVLNode<Key, Value>* n2r = n2->getRight();
    AVLNode<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    AVLNode<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }
}


template<class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::predecessor(AVLNode<Key, Value> *current) {
    if (current == nullptr) {
        return nullptr;
    }


    if (current->getLeft() != nullptr) {
        AVLNode<Key, Value> *temp = current->getLeft();
        while (temp->getRight() != nullptr) {
            temp = temp->getRight();
        }
        return temp;
    }

    AVLNode<Key, Value> *parent = current->getParent();
    while (parent != nullptr && current == parent->getLeft()) {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
}


#endif
