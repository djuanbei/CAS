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
  auto des_value_fun = [](void *v) {
    delete (int *) v;
  };
  node_manager.setValueDesFun(des_value_fun);

  Node *root = generateTree(node_manager, 30, 4, 5);

  root->dump(cout, 0);

  NodeDFSIter nodeDfsIter(root);
  std::vector<int> visit_value_vec;
  while (nodeDfsIter.next()) {
    auto current = nodeDfsIter.getCurrentNode();
    visit_value_vec.emplace_back(current->getValue<int>());
    cout << current->getValue<int>() << std::endl;
  }

}

TEST(Node, DFS_simple1) {
  NodeManager node_manager;
  auto des_value_fun = [](void *v) {
    delete (int *) v;
  };
  node_manager.setValueDesFun(des_value_fun);

  std::vector<RawNode<int>> nodes{{-1, 10}, {0, 30}, {0, 20}, {1, 100}};
  Node *root = generateTree(node_manager, nodes);
  root->dump(cout, 0);

  NodeDFSIter nodeDfsIter(root);
  std::vector<int> visit_value_vec;
  while (nodeDfsIter.next()) {
    auto current = nodeDfsIter.getCurrentNode();
    visit_value_vec.emplace_back(current->getValue<int>());
    cout << current->getValue<int>() << std::endl;
  }
  ASSERT_EQ(visit_value_vec.size(), 4);
  ASSERT_EQ(visit_value_vec[0], 10);
  ASSERT_EQ(visit_value_vec[1], 30);
  ASSERT_EQ(visit_value_vec[2], 100);
  ASSERT_EQ(visit_value_vec[3], 201);

}






