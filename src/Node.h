//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_NODE_H
#define CAS_NODE_H

#include "IDMixin.hpp"
#include "ValidAble.h"
#include "DumpAble.h"
//

#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <cassert>

namespace cas {
class Node;

typedef bool (*validFun_t)(int, void *);

typedef bool (*compareFun_t)(const Node *, const Node *);

typedef std::ostream &(*dumpFun_t)(std::ostream &, int tab_indent, const void *);

typedef void  (*valueDesFun_t)(void *);

typedef bool (*checkFun_t)(const Node *);

class Node : public IDMiXin<Node>, public DumpAble, public ValidAble {
public:

  Node(const Node &) = delete;

  Node(Node &&) = delete;

  Node &operator=(const Node &n) = delete;

  [[nodiscard]] const void *getValue() const {
    return value_;
  }
  template<typename T>
  [[nodiscard]] const T &getValue() const {
    return *((T *) value_);
  }

  /// this -> parent -> parent -> ... -> root

  std::vector<const void *> getValueBackTail() const {
    std::vector<const void *> tail;
    auto current = this;
    while (current) {
      tail.emplace_back(current->getValue());
      current = current->getParent();
    }
    return tail;
  }

  /// root-> ... parent-> this
  std::vector<const void *> getValueTail() const {
    auto re = getValueBackTail();
    std::reverse(re.begin(), re.end());
    return re;
  }

  template<typename T>
  std::vector<T> getValueBackTail(const std::function<std::vector<T>(const std::vector<const void *> &vs)> &fun) const {
    return fun(getValueBackTail());
  }

  template<typename T>
  std::vector<T> getValueTail(const std::function<std::vector<T>(const std::vector<const void *> &vs)> &fun) const {
    return fun(getValueTail());
  }

  /// this -> parent -> parent -> ... -> root

  template<typename T>
  std::vector<T> getValueBackTail() const {
    std::vector<T> tail;
    auto current = this;
    while (current) {
      tail.emplace_back(current->getValue<T>());
      current = current->getParent();
    }
    return tail;
  }
  /// root-> ... parent-> this
  template<typename T>
  std::vector<T> getValueTail() const {
    auto re = getValueBackTail<T>();
    std::reverse(re.begin(), re.end());
    return re;
  }

  void releaseValue(const std::function<void(void *)> &d_fun) {
    d_fun(value_);
    value_ = nullptr;
  }

  int getType() const {
    return type_;
  }

  [[nodiscard]] uint64_t getStatus() const {
    return status_;
  }

  void setStatus(uint64_t s) {
    status_ = s;
  }

  void addChild(Node *node) {
    node->parent_ = this;
    child_.emplace_back(node);
  }

  void removeChild(size_t ndex);

  void setValueValidFun(validFun_t fun) {
    value_valid_fun = fun;
  }

  void setValueDumpFun(dumpFun_t fun) {
    value_dump_fun = fun;
  }

  void setValueDesFun(valueDesFun_t fun) {
    value_des_fun = fun;
  }

  [[nodiscard]]  const std::vector<Node *> getChild() const {
    return child_;
  }

  size_t getChildNum() const {
    return child_.size();
  }

  const Node *getChild(size_t id) const {
    return child_[id];
  }

  Node *getChild(size_t id) {
    if (id >= child_.size()) {
      return nullptr;
    }
    return child_[id];
  }

  [[nodiscard]] bool isLeaf() const {
    return 0 == getChildNum();
  }

  Node *getParent() {
    return parent_;
  }

  const Node *getParent() const {
    return parent_;
  }

  void norm(compareFun_t fun);

  [[nodiscard]]  int getNodeNum() const;

  [[nodiscard]]  int getLeafNodeNum() const;

  [[nodiscard]]  int getNodeNumWithStatus(uint64_t status) const;

  [[nodiscard]]  int getLeafNodeNumWithStatus(uint64_t status) const;

  [[nodiscard]]   int getNodeNumWithType(int t) const;

  [[nodiscard]]   int getLeafNodeNumWithWithType(int t) const;

  void getAllNode(std::vector<Node *> &nodes) const;

  void getAllNodeWithType(std::vector<Node *> &nodes, int t) const;

  void getAllNodeWithStatus(std::vector<Node *> &nodes, uint64_t status) const;

  void getAllLeafNode(std::vector<Node *> &nodes) const;

  void getAllLeafNodeWithType(std::vector<Node *> &nodes, int type) const;

  void getAllLeafNodeWithStatus(std::vector<Node *> &nodes, uint64_t status) const;

  [[nodiscard]]  int getDepth() const;

  /**
   * @return true iff there is node been removed
   */

  bool removeNodeWithStatus(uint64_t status);
/**
   * @return true iff there is node been removed
   */
  bool removeLeafNodeWithStatus(uint64_t status, bool recursive = true);

  /**
   *  remove node when fun(n) hold
   */
  bool removeNode(checkFun_t fun);
  /**
   * remove leaf node when fun(n) hold
   */

  bool removeLeafNode(checkFun_t fun, bool recursive = true);

  friend class NodeManager;

  std::ostream &dump(std::ostream &out, int tab_indent = 0) const override;

  [[nodiscard]] bool valid() const override;

private:
  Node() = default;

  explicit Node(void *v) : value_(v) {

  }

  int type_{0};
  std::vector<Node *> child_;
  mutable uint64_t status_{0};
  void *value_{nullptr};
  Node *parent_{nullptr};

  validFun_t value_valid_fun{nullptr};
  dumpFun_t value_dump_fun{nullptr};

  valueDesFun_t value_des_fun{nullptr};

  static int nextId() {
    static int global_id = 0;
    return global_id++;
  }

};

static inline std::pair<Node *, bool> removeNodeWithStatus(Node *node, uint64_t statue) {
  assert(node);
  if (node->getStatus() == statue) {
    return {nullptr, true};
  }
  auto re = node->removeNodeWithStatus(statue);
  return {node, re};
}

static inline std::pair<Node *, bool> removeLeafNodeWithStatus(Node *node, uint64_t status, bool recursive = true) {
  assert(node);
  if (node->isLeaf() && node->getStatus() == status) {
    return {nullptr, true};
  }
  auto re = node->removeLeafNodeWithStatus(status, recursive);
  return {node, re};
}

static inline std::pair<Node *, bool> removeNode(Node *node, checkFun_t fun) {
  assert(node);
  if (fun(node)) {
    return {nullptr, true};
  }
  auto re = node->removeNode(fun);
  return {node, re};
}

/**
  * remove leaf node when fun(n) hold
  */

static inline std::pair<Node *, bool> removeLeafNode(Node *node, checkFun_t fun, bool recursive = true) {
  assert(node);
  if (node->isLeaf() && fun(node)) {
    return {nullptr, true};
  }
  auto re = node->removeLeafNode(fun, recursive);
  return {node, re};

}

static inline std::vector<Node *> getAllNode(Node *root) {
  std::vector<Node *> nodes;
  nodes.emplace_back(root);
  root->getAllNode(nodes);
  return nodes;
}

static inline std::vector<Node *> getAllNodeWithType(Node *root, int type) {
  std::vector<Node *> nodes;
  if (root->getType() == type) {
    nodes.emplace_back(root);
  }
  root->getAllNodeWithType(nodes, type);
  return nodes;
}

static inline std::vector<Node *> getAllNodeWithStatus(Node *root, uint64_t statue) {
  std::vector<Node *> nodes;
  if (root->getStatus() == statue) {
    nodes.emplace_back(root);
  }
  root->getAllNodeWithStatus(nodes, statue);
  return nodes;

}

static inline std::vector<Node *> getAllLeafNode(Node *root) {
  std::vector<Node *> nodes;
  if (root->isLeaf()) {
    return {root};
  }
  root->getAllLeafNode(nodes);
  return nodes;

}

static inline std::vector<Node *> getAllLeafNodeWithType(Node *root, int type) {
  std::vector<Node *> nodes;
  if (root->isLeaf()) {
    if (root->getType() == type) {
      return {root};
    }
    return {};
  }

  root->getAllLeafNodeWithType(nodes, type);
  return nodes;
}

static inline std::vector<Node *> getAllLeafNodeWithStatus(Node *root, uint64_t statue) {
  std::vector<Node *> nodes;
  if (root->isLeaf()) {
    if (root->getStatus() == statue) {
      return {root};
    }
    return {};
  }
  root->getAllLeafNodeWithStatus(nodes, statue);
  return nodes;
}

class NodeManager {

public:
  NodeManager() = default;
  NodeManager(std::function<void(void *)> d_fun) : value_des_fun_(std::move(d_fun)) {

  }
  ~NodeManager();
  //Node *createNode();

  Node *createNode(void *v);

  void setValueDesFun(const std::function<void(void *)> &d_fun) {
    value_des_fun_ = std::move(d_fun);
  }

private:
  std::vector<Node *> node_vec_;
  std::function<void(void *)> value_des_fun_{nullptr};

};

///DFS
struct NodeIt {
  NodeIt() = default;

  NodeIt(Node *n, int i) : node(n), ch_index(i) {

  }

  Node *getCurrentNode() {
    if (ch_index < 0) {
      return node;
    }
    return node->getChild(ch_index);
  }

  bool withNextSlide() const {
    return ch_index + 1 < node->getChildNum();
  }

  Node *node{nullptr};
  int ch_index{0};

};

///DFS
class NodeDFSIter {

public:
  explicit NodeDFSIter(Node *root) {
    index_seq.emplace_back(root, -2);
  }

  bool next();

  void nextSlide();

  void downChild();

  void upParent();

  Node *getCurrentNode() {
    return index_seq.back().getCurrentNode();
  }

protected:
  bool valid(class Node *n) const {
    return (n != nullptr) && (n->getValue() != nullptr);
  }

private:

  std::vector<NodeIt> index_seq;

};
///DFS

struct ConstDFSNodeIt {
  ConstDFSNodeIt() = default;

  ConstDFSNodeIt(const Node *n, int i) : node(n), ch_index(i) {

  }

  const Node *getCurrentNode() const {
    return node->getChild(ch_index);
  }

  bool withNextSlide() const {
    return ch_index + 1 < node->getChildNum();
  }

  const Node *node{nullptr};
  int ch_index{0};
};

class ConstDFSNodeIter {

public:

  explicit ConstDFSNodeIter(Node *root) {
    index_seq.emplace_back(root, -2);
  }

  void nextSlide();

  void downChild();

  void upParent();

  bool next();

  [[nodiscard]] const Node *getCurrentNode() const {
    return index_seq.back().getCurrentNode();
  }

private:
  std::vector<ConstDFSNodeIt> index_seq;
};

}

#endif //CAS_NODE_H
