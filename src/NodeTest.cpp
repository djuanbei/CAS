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

TEST(Node, DFS_simple) {
  NodeManager node_manager;
  Node *root = generateTree(node_manager, 30, 4, 5);

  root->dump(cout, 0);

  NodeDFSIter nodeDfsIter(root);
  while (nodeDfsIter.next()) {
    auto current = nodeDfsIter.getCurrentNode();
    cout << *((int *) current->getValue()) << std::endl;
  }

}





