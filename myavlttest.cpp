#include "avlbst.h"
#include <iostream>


int main() {
    AVLTree<int, char> tree;
    tree.insert(std::make_pair(3, 'A'));
     tree.print();
     tree.insert(std::make_pair(2, 'B'));
      tree.print();
     tree.insert(std::make_pair(1, 'C'));
      tree.print();
    tree.insert(std::make_pair(10, 'D'));
     tree.print();
    tree.insert(std::make_pair(9, 'F'));
     tree.print();
    tree.insert(std::make_pair(-1, 'K'));
    tree.print();
    tree.insert(std::make_pair(11, 'L'));
     tree.print();
    tree.insert(std::make_pair(12, 'M'));
     tree.print();
    tree.insert(std::make_pair(13, 'N'));
     tree.print();
    tree.insert(std::make_pair(14, 'O'));
     tree.print();
   


    // Add more test cases if necessary
    return 0;
}
