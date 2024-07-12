//
// Created by yun dai on 2024/7/12.
//
#include <gtest/gtest.h>
#include "Node.h"
#include "TreeAlg.h"
#include <iostream>

using namespace testing;
using namespace cas;
using namespace std;


TEST(Node, simple) {
    Node *root = generateTree(10, 3, 3);

    root->dump(cout, 0);

}

