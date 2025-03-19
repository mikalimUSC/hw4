#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int findLevels(Node *root);

bool equalPaths(Node * root)
{
    if(root==nullptr){
        return true;
    }

    if(root->left != nullptr && root->right == nullptr){
        if(equalPaths(root->right)){
            return true;
        }
        return false;
    }

    if(root->left == nullptr && root->right != nullptr){
        if(equalPaths(root->left)){
            return true;
        }
        return false;
    }
    int left = findLevels(root->left);
    int right = findLevels(root->right);

    // cout << "left: " << left<<endl;
    // cout << "right: " << right<<endl;

    return left==right;
}


//returns number of levels of one branch(determiend by direction)
int findLevels(Node *root) {
   
    if (!root ) {
        return 0;
    }
     //cout << " KEY: " << root->key<<endl;

    int left = 0;
    int right = 0;

    if (root->left != nullptr){
        left = findLevels(root->left);
      //  cout << "left is received as  " << left << endl;
    }

     if (root->right != nullptr){
        right = findLevels(root->right);
        // cout << "right is received as  " << right << endl;
    }

    //cout << "findLevels- right:  " << right << endl;
  //  cout << "findLevels- left:  " << left << endl;
    if(right > left){
        //cout << "returning " << 1 + right<<endl;
   
        return 1+ right;
    }else{
          //   cout << "returning " << 1 + left<<endl;
        return 1+ left;
    }
}

//b 
// right = findLevels(d) = 1
//left = 0;

//d 
//left =0;
//right =0;
//retuen 1;