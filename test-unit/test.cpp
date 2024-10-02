#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../TreeNode.h"
#include "../Commands.h"


TEST_CASE("Incorrect Insert Command", "[flag]"){

    AVLTree tree;   // Create a Tree object
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    std::vector<int> actualOutput = tree.inorder();
    std::vector<int> expectedOutput = {1, 2, 3};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE() {


}

TEST_CASE() {


}