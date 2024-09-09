//
// Created by yun dai on 2024/7/8.
//

#include "Node.h"
#include <cassert>
#include <string>

namespace cas {

using namespace std;

int Node::getNodeNum() const {
  int num = 1;
  for (auto &d : child_) {
    num += getNodeNum();
  }
  return num;

}

int Node::getLeafNodeNum() const {
  if (child_.empty()) {
    return 1;
  }

  int num = 0;
  for (auto d : child_) {
    num += getLeafNodeNum();
  }
  return num;
}

int Node::getNodeNumWithStatus(uint64_t status) const {
  int num = 0;
  if (getStatus() == status) {
    num++;
  }
  for (auto d : child_) {
    num += getNodeNumWithStatus(status);
  }
  return num;

}

int Node::getLeafNodeNumStatus(uint64_t status) const {
  if (child_.empty()) {
    return getStatus() == status ? 1 : 0;
  }
  int num = 0;
  for (auto d : child_) {
    num += getLeafNodeNumStatus(status);
  }
  return num;

}

int Node::getDepth() const {

  int level = 0;

  for (auto d : child_) {
    level = std::max(level, d->getDepth());
  }

  return level + 1;
}

/**
  * @return true iff there is node been removed
  */

bool Node::removeNodeWithStatus(uint64_t status) {
  auto it = remove_if(child_.begin(), child_.end(), [=](auto d) {
    return d->getStatus() == status;
  });
  bool re = false;
  if (it != child_.end()) {
    re = true;
  }
  child_.resize(it - child_.begin());
  for (auto d : child_) {
    if (d->removeLeafNodeWithStatus(status)) {
      re = true;
    }
  }
  return re;
}
/**
   * @return true iff there is node been removed
   */
bool Node::removeLeafNodeWithStatus(uint64_t status, bool recursive) {
  auto it = remove_if(child_.begin(), child_.end(), [=](auto d) {
    return d->isLeaf() && d->getStatus() == status;
  });

  bool direct_re = false;
  if (it != child_.end()) {
    direct_re = true;
  }

  child_.resize(it - child_.begin());
  bool ch_re = false;
  for (auto d : child_) {
    if (d->removeLeafNodeWithStatus(status, recursive)) {
      ch_re = true;
    }
  }

  if (ch_re) {
    it = remove_if(child_.begin(), child_.end(), [=](auto d) {
      return d->isLeaf() && d->getStatus() == status;
    });
    child_.resize(it - child_.begin());
  }

  return direct_re || ch_re;

}

bool Node::valid() const {
  if (value_valid_fun) {
    if (!value_valid_fun(type_, value_)) {
      return false;
    }
  }

  for (auto d : child_) {
    if (d->parent_ != nullptr) {
      return false;
    }
  }

  return std::all_of(child_.begin(), child_.end(), [](auto &d) {
    return d->valid();
  });
}

std::ostream &Node::dump(std::ostream &out, int tab_indent) const {
  out << string(tab_indent, '\t');
  out << "ID: " << getId() << ", " << "type: " << type_ << ", " << ", status: " << status_;

  if (value_dump_fun) {
    value_dump_fun(out, 1, value_);
  }
  out << "\n";
  for (auto d : child_) {
    d->dump(out, tab_indent + 1);
  }
  return out;

}

void NodeDFSIter::nextSlide() {
  index_seq.back().ch_index++;
  assert(index_seq.back().ch_index < index_seq.back().node->getChildNum());
}

void NodeDFSIter::downChild() {
  auto current = getCurrentNode();
  assert(current);
  assert(current->getChildNum() > 0);
  index_seq.emplace_back(current, 0);
}

void NodeDFSIter::upParent() {
  assert(!index_seq.empty());
  index_seq.pop_back();

}

bool NodeDFSIter::next() {
  if (index_seq.empty()) {
    return false;
  }

  auto current = getCurrentNode();

  assert(current);
  if (index_seq.size() == 1 && index_seq[0].ch_index == -2) {
    index_seq[0].ch_index = -1;
    return true;
  }

  if (index_seq.size() == 1 && index_seq[0].ch_index == -1) {
    if (current->getChildNum() > 0) {
      index_seq[0].ch_index = 0;
      return true;
    }
    return false;
  }

  if (current->getChildNum() > 0) {
    downChild();
    return true;
  }
  while (!index_seq.empty()) {
    if (index_seq.back().withNextSlide()) {
      nextSlide();
      return true;
    }
    upParent();
  }
  return false;

}

void ConstDFSNodeIter::nextSlide() {
  index_seq.back().ch_index++;
  assert(index_seq.back().ch_index < index_seq.back().node->getChildNum());
}

void ConstDFSNodeIter::downChild() {
  auto current = getCurrentNode();
  assert(current);
  assert(current->getChildNum() > 0);
  index_seq.emplace_back(current, 0);
}

void ConstDFSNodeIter::upParent() {
  assert(!index_seq.empty());
  index_seq.pop_back();

}

bool ConstDFSNodeIter::next() {
  if (index_seq.empty()) {
    return false;
  }

  auto current = getCurrentNode();

  assert(current);
  if (index_seq.size() == 1 && index_seq[0].ch_index == -2) {
    index_seq[0].ch_index = -1;
    return true;
  }

  if (index_seq.size() == 1 && index_seq[0].ch_index == -1) {
    if (current->getChildNum() > 0) {
      index_seq[0].ch_index = 0;
      return true;
    }
    return false;
  }

  if (current->getChildNum() > 0) {
    downChild();
    return true;
  }
  while (!index_seq.empty()) {
    if (index_seq.back().withNextSlide()) {
      nextSlide();
      return true;
    }
    upParent();
  }
  return false;

}

NodeManager::~NodeManager() {
  if (value_des_fun_) {
    for (auto &n : node_vec_) {
      n->releaseValue(value_des_fun_);
    }
  }
  for (auto n : node_vec_) {
    delete n;
  }
  node_vec_.clear();

}
Node *NodeManager::createNode() {
  auto re = new Node();
  node_vec_.emplace_back(re);
  return re;
}

Node *NodeManager::createNode(void *v) {
  auto re = new Node(v);
  node_vec_.emplace_back(re);
  return re;
}

}
