#include "avlbst.h"
#include <iostream>


int main() {
 AVLTree<std::string, std::string> testTree;

    testTree.insert(std::make_pair("Hello World", "!!!"));
    testTree.print();

    // Add more test cases if necessary
    return 0;
}
