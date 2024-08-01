//
// Created by yun dai on 2024/7/9.
//
#include "TreeAlg.h"
#include "Node.h"
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>
#include <iostream>

namespace cas {
using namespace std;

namespace {
Node *build(NodeManager &manager, const std::vector<int> &value, int &i, int level, int degree) {
  assert(level > 0);
  assert(i < value.size());
  level--;
  auto v = new int;
  *v = value[i++];
  auto re = manager.createNode(v);
  if (level > 0) {
    for (int d = 0; d < degree && i < value.size(); d++) {
      re->addChild(build(manager, value, i, level, degree));
    }
  }
  auto dump = [](std::ostream &out, int tab_indent, const void *v) -> std::ostream & {
    return out << string(tab_indent, '\t') << ", value: " << (*((int *) v));
  };
  re->setValueDumpDun(dump);

  return re;

}
}

Node *generateTree(NodeManager &manager, int node_num, int degree, int depth) {
  assert(node_num > 0);
  assert(degree > 0);
  assert(depth > 0);
  assert(depth < 6);
  assert(degree < 5);
  std::vector<int> node_value(node_num);
  for (size_t i = 0; i < node_value.size(); i++) {
    node_value[i] = i;
  }
  shuffle(node_value.begin(), node_value.end(), std::default_random_engine());

  int i = 0;
  return build(manager, node_value, i, depth, degree);

}

void dfs(const Node *node,
         nodeCheck_t is_ok,
         handle_fun_t before_visit,
         handle_fun_t visit_fun,
         handle_fun_t post_visit_fun) {
  assert(node);

  std::vector<std::pair<const Node *, int> > wait_S;
  if (is_ok(node)) {
    wait_S.emplace_back(node, -1);
  }
  while (!wait_S.empty()) {
    auto e = wait_S.back();
    if (e.second == -1) {
      assert(is_ok(e.first));
      before_visit(e.first);
      visit_fun(e.first);
    }
    e.second++;
    if (e.second >= e.first->getChildNum()) {
      post_visit_fun(e.first);
      wait_S.pop_back();
      continue;
    }
    if (is_ok(e.first->getChild(e.second))) {
      wait_S.emplace_back(e.first->getChild(e.second), -1);
    }
  }

}

void dfs(Node *node,
         NodeManager &manager,
         nodeCheck_t
         is_ok,
         modify_handle_fun_t before_visit,
         modify_handle_fun_t
         visit_fun,
         modify_handle_fun_t post_visit_fun
) {

  assert(node);

  std::vector<std::pair<Node *, int> > wait_S;
  if (is_ok(node)) {
    wait_S.emplace_back(node, -1);
  }
  while (!wait_S.empty()) {
    auto e = wait_S.back();
    if (e.second == -1) {
      assert(is_ok(e.first));
      before_visit(manager, e.first);
      visit_fun(manager, e.first);
    }
    e.second++;
    if (e.second >= e.first->getChildNum()) {
      post_visit_fun(manager, e.first);
      wait_S.pop_back();
      continue;
    }
    if (is_ok(e.first->getChild(e.second))) {
      wait_S.emplace_back(e.first->getChild(e.second), -1);
    }
  }

}

void dfs(const Node *node, nodeCheck_t is_ok, handle_fun_t fun) {
  assert(node);

  std::vector<std::pair<const Node *, int> > wait_S;
  if (is_ok(node)) {
    wait_S.emplace_back(node, -1);
  }
  while (!wait_S.empty()) {
    auto e = wait_S.back();
    if (e.second == -1) {
      assert(is_ok(e.first));
      fun(e.first);
    }
    e.second++;
    if (e.second >= e.first->getChildNum()) {
      wait_S.pop_back();
      continue;
    }
    if (is_ok(e.first->getChild(e.second))) {
      wait_S.emplace_back(e.first->getChild(e.second), -1);
    }
  }

}

}