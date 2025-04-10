#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>
#include "avlbst.h"  // Adjust this include if needed

void printStatus(const std::string& msg) {
    std::cout << "\n=== " << msg << " ===\n";
}

int main() {
    AVLTree<int, std::string> tree;

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // ===== 30 Unique Random Inserts =====
    printStatus("Inserting 30 Random Elements");

    std::vector<int> insertedKeys;
    while (insertedKeys.size() < 30) {
        int key = std::rand() % 500 + 1;  // Range [1, 500]
        if (std::find(insertedKeys.begin(), insertedKeys.end(), key) == insertedKeys.end()) {
            insertedKeys.push_back(key);
            tree.insert({key, "Val" + std::to_string(key)});
            std::cout << "Inserted: " << key << "\n";
        }
    }

    std::cout << "\nTree after 30 inserts:\n";
    tree.print();
    assert(tree.isBalanced());

    // ===== 30 Random Removals from the Inserted Keys =====
    printStatus("Removing All 30 Elements in Random Order");

    std::random_shuffle(insertedKeys.begin(), insertedKeys.end());

    for (int i = 0; i < 30; ++i) {
        int key = insertedKeys[i];
        tree.remove(key);
        std::cout << "Removed: " << key << "\n";
    }

    std::cout << "\nTree after 30 removals:\n";
    tree.print();
    assert(tree.empty());
    assert(tree.isBalanced());

    printStatus("Final Check");
    std::cout << "AVL Tree is balanced and empty after 30 inserts and 30 removals ✅\n";

    return 0;
}
