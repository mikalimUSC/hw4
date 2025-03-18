#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int checkPathLength(Node *root, int expectedLength);

bool equalPaths(Node * root)
{
    if(root==nullptr){
        return true;
    }
    if(root->right == nullptr && root->left == nullptr){
        return true;
    }
    int pathCount =  checkPathLength(root, -1);
    return pathCount != 0;
}

//expected length -1 is default/when you havent checked any paths yet
int checkPathLength(Node *root, int expectedLength) {
    if(root->right == nullptr && root->left == nullptr){
        if(expectedLength == -1) {
            return 0; 
        } else {
            return (expectedLength == 0); 
        }
    }

    int leftSum = -1;
    int rightSum = -1;

    if(root->left != nullptr) {
        leftSum = 1 + checkPathLength(root->left, -1);
    }

    if(root->right != nullptr) {
        rightSum = 1 + checkPathLength(root->right, -1);
    }


    if(leftSum != -1 && rightSum != -1) {
        if(leftSum == rightSum) {
            if(expectedLength == -1) {
                return leftSum; 
            } else {
                return (expectedLength == leftSum);
            }
        }
        return 0; 
    }
    int validPathLength;
    if (leftSum != -1) {
        validPathLength = leftSum;
    } else {
        validPathLength = rightSum;
    }
    if(expectedLength == -1) {
        return validPathLength; 

    }
}
