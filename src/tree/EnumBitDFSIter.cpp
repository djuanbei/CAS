//
// Created by yun dai on 2024/9/21.
//

#include "EnumBitDFSIter.h"
#include <cassert>
#include <vector>
namespace cas {
using namespace std;
EnumBitDFSIter::EnumBitDFSIter(int len) : N(len) {
  assert(len > 0);
  auto des_fun = [](void *v) {
    delete ((std::vector<int> *) (v));
  };
  node_manager.setValueDesFun(des_fun);

  auto vv = new std::vector<int>();
  /// index start 0 is dummy value;
  vv->emplace_back(0);
  auto root = node_manager.createNode(vv);
  index_seq.emplace_back(root, -1);
}

bool EnumBitDFSIter::next() {
  if (index_seq.empty()) {
    return false;
  }
  auto current = getCurrentNode();
  assert(valid(current));
  appendChild(current);

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

void EnumBitDFSIter::nextSlide() {
  index_seq.back().ch_index++;
  assert(index_seq.back().ch_index < index_seq.back().node->getChildNum());
}

void EnumBitDFSIter::downChild() {

  auto current = getCurrentNode();
  assert(current);
  assert(current->getChildNum() > 0);
  index_seq.emplace_back(current, 0);
}

void EnumBitDFSIter::upParent() {
  assert(!index_seq.empty());
  index_seq.pop_back();
}

}