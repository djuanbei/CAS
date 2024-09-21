//
// Created by yun dai on 2024/9/21.
//

#ifndef CAS_SRC_BINENUMVALUETREE_H
#define CAS_SRC_BINENUMVALUETREE_H
/**
 * Enum all value od  N len bit
 *
 * x_1: 0
 * x_1: 0, x_2:0
 * x_1: 0, x_2:0, x_3: 0
 * x_1: 0, x_2:0, x_3: 1
 * x_1: 0, x_2:1
 * x_1: 0, x_2:1, x_3:0
 * x_1: 0, x_2:1, x_3:1
 * x_1: 1
 * x_1: 1, x_2: 0
 * x_1: 1, x_2: 0, x_3: 0
 * x_1: 1, x_2: 0, x_3:1
 * x_1, 1, x_2: 1
 * x_1: 1, x_2:1, x_3:0
 * x_1: 1, x_2:1, x_3:1
 *
 */

#include "../Node.h"
namespace cas {
class EnumBitDFSIter {

public:
  EnumBitDFSIter(int len);

  bool next();

  void nextSlide();

  void downChild();

  void upParent();

  Node *getCurrentNode() {
    return index_seq.back().getCurrentNode();
  }

protected:
  bool valid(const Node *n) const {
    return (n != nullptr) && (n->getValue() != nullptr) && (n->getValue<std::vector<int>>().size() > 0);
  }
  bool withChild(const Node *n) const {
    auto &n_v = n->getValue<std::vector<int>>();
    return std::abs(n_v.back()) < N;
  }

  bool withNextSlide(const NodeIt &it) const {
    return it.ch_index < 2;
  }

  void appendChild(Node *node) {
    if (node->isLeaf()) {
      auto &nv = node->getValue<std::vector<int>>();
      auto next_v = std::abs(nv.back()) + 1;
      if (next_v <= N) {
        auto vv1 = new std::vector<int>();
        vv1->emplace_back(next_v);
        auto ch1 = node_manager.createNode(vv1);
        node->addChild(ch1);
        auto vv2 = new std::vector<int>();
        vv2->emplace_back(-next_v);
        auto ch2 = node_manager.createNode(vv2);
        node->addChild(ch2);
      }

    }

  }

private:
  int N{0};
  NodeManager node_manager;
  std::vector<NodeIt> index_seq;

};

}

#endif //CAS_SRC_BINENUMVALUETREE_H
