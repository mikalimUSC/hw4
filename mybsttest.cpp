#include <iostream>
#include "bst.h"

int main() {
    BinarySearchTree<uint16_t, uint16_t> testTree;

 testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(10, 0x5a));

	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(4, 4));
	testTree.insert(std::make_pair(17, 159));

    testTree.print();

    std::cout << "Balanced? : " << testTree.isBalanced() << std::endl;
    /**
     * 
     * 
     *                10
     *           2         50
     *              5
     *                8
     * 
     * 
     * */
   

    return 0;
}
