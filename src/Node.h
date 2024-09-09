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

namespace cas {

typedef bool (*validFun_t)(int, void *);

typedef std::ostream &(*dumpFun_t)(std::ostream &, int tab_indent, const void *);

typedef void  (*valueDesFun_t)(void *);

class Node : public IDMiXin<Node>, public DumpAble, public ValidAble {
 public:
  Node(const Node &) = delete;

  Node(Node &&) = delete;

  Node &operator=(const Node &n) = delete;

  const void *getValue() const {
    return value_;
  }
  void releaseValue(const std::function<void(void *)> &d_fun) {
    d_fun(value_);
    value_ = nullptr;
  }

  uint64_t getStatus() const {
    return status_;
  }

  void addChild(Node *node) {
    child_.emplace_back(node);
  }

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

  int getChildNum() const {
    return child_.size();
  }

  const Node *getChild(int id) const {
    return child_[id];
  }

  Node *getChild(int id) {
    if (id >= child_.size()) {
      return nullptr;
    }
    return child_[id];
  }
  bool isLeaf() const {
    return 0 == getChildNum();
  }

  [[nodiscard]]  int getNodeNum() const;

  [[nodiscard]]  int getLeafNodeNum() const;

  [[nodiscard]]  int getNodeNumWithStatus(uint64_t status) const;

  [[nodiscard]]  int getLeafNodeNumStatus(uint64_t status) const;

  [[nodiscard]]  int getDepth() const;
  /**
   * @return true iff there is node been removed
   */

  bool removeNodeWithStatus(uint64_t status);
/**
   * @return true iff there is node been removed
   */
  bool removeLeafNodeWithStatus(uint64_t status, bool recursive = true);

  friend class NodeManager;

  std::ostream &dump(std::ostream &out, int tab_indent = 0) const override;

  [[nodiscard]] bool valid() const override;

 private:
  Node() = default;

  explicit Node(void *v) : value_(v) {

  }

  int type_{0};
  std::vector<Node *> child_;
  uint64_t status_{0};
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

class NodeManager {

 public:
  NodeManager() = default;
  NodeManager(std::function<void(void *)> d_fun) : value_des_fun_(std::move(d_fun)) {

  }
  ~NodeManager();
  Node *createNode();

  Node *createNode(void *v);

  void setValueDesFun(const std::function<void(void *)> &d_fun) {
    value_des_fun_ = std::move(d_fun);
  }

 private:
  std::vector<Node *> node_vec_;
  std::function<void(void *)> value_des_fun_{nullptr};

};

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

  Node *getCurrentNode() {
    return index_seq.back().getCurrentNode();
  }

  void nextSlide();

  void downChild();

  void upParent();

 private:

  std::vector<NodeIt> index_seq;

};

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

//Node *createNode();
//
//Node *createNode(void *v);

}

#endif //CAS_NODE_H
