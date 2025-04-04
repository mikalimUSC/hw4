#include <iostream>
#include "bst.h"

int main() {
    BinarySearchTree<int, std::string> bst;

    // Insert some key-value pairs
    bst.insert(std::make_pair(10, "ten"));
    bst.insert(std::make_pair(50, "fifty"));
    bst.insert(std::make_pair(2, "two"));
    bst.insert(std::make_pair(5, "five"));
     bst.insert(std::make_pair(8, "eight"));
      bst.insert(std::make_pair(1, "one"));
        bst.insert(std::make_pair(15, "fifteen"));
    bst.insert(std::make_pair(31, "thirty one"));
    bst.insert(std::make_pair(-1, "negative one"));
    bst.insert(std::make_pair(100, "hundred"));
    bst.insert(std::make_pair(101, "hundred and one"));
    bst.insert(std::make_pair(102, "hundred and two"));
    bst.insert(std::make_pair(103, "hundred and three"));
   

    // Print the tree
    std::cout << "Binary Search Tree after insertion:\n";
    bst.print();

    std::cout << "Is Balanced? : " << bst.isBalanced()<< std::endl;

    // Test the iterator
    std::cout << "\nIterating through the tree:\n";
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ")\n";
    }


    std::cout << "removing 102" <<std::endl;
    bst.remove(102);
     std::cout << "removed 102, now printing" <<std::endl;
    bst.print();

     std::cout << "removing 103" <<std::endl;
    bst.remove(103);
     std::cout << "removed 103, now printing" <<std::endl;
    bst.print();

    std::cout << "Is Balanced? : " << bst.isBalanced()<< std::endl;

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
