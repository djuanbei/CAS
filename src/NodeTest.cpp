//
// Created by yun dai on 2024/7/12.
//
//
#include <gtest/gtest.h>
#include <iostream>
//
#include "Node.h"
#include "TreeAlg.h"

#include "tree/EnumBitDFSIter.h"
using namespace testing;
using namespace cas;
using namespace std;

TEST(Node, DFS_simple) {
  NodeManager node_manager;
  auto des_value_fun = [](void *v) { delete (int *)v; };
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
  auto des_value_fun = [](void *v) { delete (int *)v; };
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
  ASSERT_EQ(visit_value_vec[3], 20);
}

TEST(EnumBitDFSIter, simple) {

  EnumBitDFSIter enum_dfs_iter(3);

  auto value_merge_fun = [](const std::vector<const void *> &v_s) {
    std::vector<int> re;
    for (auto n : v_s) {
      auto vv_s = (const std::vector<int> *)n;
      re.insert(re.end(), vv_s->begin(), vv_s->end());
    }
    return re;
  };

  NodeDFSIter nodeDfsIter(enum_dfs_iter.getRoot(), enum_dfs_iter.rootIsFake());

  int node_num = 0;
  while (nodeDfsIter.next(enum_dfs_iter.getChecker(),
                          enum_dfs_iter.appendChildFun())) {
    node_num++;
    auto current = nodeDfsIter.getCurrentNode();
    ASSERT_TRUE(current->isLeaf());
    auto vs = current->getValueTail<int>(value_merge_fun);
    for (size_t i = 1; i < vs.size(); i++) {
      cout << " " << vs[i];
    }
    cout << endl;
  }
  ASSERT_EQ(node_num, 14);
}

TEST(EnumBitDFSIter, simple1) {

  EnumBitDFSIter enum_dfs_iter(10);

  auto value_merge_fun = [](const std::vector<const void *> &v_s) {
    std::vector<int> re;
    for (auto n : v_s) {
      auto vv_s = (const std::vector<int> *) n;
      re.insert(re.end(), vv_s->begin(), vv_s->end());
    }
    return re;
  };

  NodeDFSIter nodeDfsIter(enum_dfs_iter.getRoot(), enum_dfs_iter.rootIsFake());

  auto checker = [&](const Node *node) {
    auto vs = node->getValueTail<int>(value_merge_fun);
    return vs.size() < 4 || (vs.back() > 0 && vs[vs.size() - 2] > 0);
  };
  int num = 0;
  while (nodeDfsIter.next(checker, enum_dfs_iter.appendChildFun())) {
    num++;
    if (num == 200) {
      nodeDfsIter.updateVisitNode([](Node *n) {
        n->setStatus(1);
        return true;
      });

      nodeDfsIter.removeVisitNode([](const Node *n) {
        return n->getStatus() == 1;
      });
    }

    auto current = nodeDfsIter.getCurrentNode();
    auto vs = current->getValueTail<int>(value_merge_fun);
    for (size_t i = 1; i < vs.size(); i++) {
      cout << " " << vs[i];
    }
    cout << endl;
  }

  enum_dfs_iter.getRoot()->dump(std::cout, 0);

}







