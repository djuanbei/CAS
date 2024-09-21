//
// Created by yun dai on 2024/9/21.
//

#ifndef CAS_SRC_BINENUMVALUETREE_H
#define CAS_SRC_BINENUMVALUETREE_H
#include "DFSIterInterface.h"
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
class EnumBitDFSIter : public DFSIterInterface {

public:
  EnumBitDFSIter(int len);

  [[nodiscard]]  bool rootIsFake() const override {
    return true;
  }
  [[nodiscard]] Node *getRoot() const override {
    return root;
  }
  [[nodiscard]] std::function<bool(const Node *)> getChecker() const override {
    return [](const Node *) {
      return true;
    };
  }

  [[nodiscard]]  std::function<void(Node *)> appendChildFun() override {
    return [&](Node *node) {
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
    };
  }

private:
  int N{0};
  NodeManager node_manager;
  Node *root{nullptr};

};

}

#endif //CAS_SRC_BINENUMVALUETREE_H
