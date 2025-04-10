#include "avlbst.h"
#include <iostream>


int main() {
 AVLTree<std::string, std::string> testTree;

 testTree.insert(std::make_pair("A", "Apple"));
    testTree.print();

    testTree.insert(std::make_pair("B", "Baba"));
    testTree.print();

    testTree.insert(std::make_pair("C", "Car"));
    testTree.print();

    testTree.insert(std::make_pair("D", "Dog"));
    testTree.print();

    testTree.insert(std::make_pair("E", "Eggplant"));
    testTree.print();

    testTree.insert(std::make_pair("F", "Fry"));
    testTree.print();

    testTree.insert(std::make_pair("G", "Gravy"));
    testTree.print();



    //
    testTree.remove("D");
    testTree.print();
    testTree.remove("A");
    testTree.print();
    testTree.remove("B");
    testTree.print();
    testTree.remove("G");
    testTree.print();



    // Add more test cases if necessary
    return 0;
}
