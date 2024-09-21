//
// Created by yun dai on 2024/9/21.
//

#ifndef CAS_SRC_TREE_DFSITERINTERFACE_H
#define CAS_SRC_TREE_DFSITERINTERFACE_H
#include "../Node.h"
#include <functional>
namespace cas {

class DFSIterInterface {
public:
  virtual ~DFSIterInterface() = default;
  [[nodiscard]] virtual bool rootIsFake() const = 0;
  [[nodiscard]] virtual Node *getRoot() const = 0;
  [[nodiscard]] virtual std::function<bool(const Node *)> getChecker() const = 0;
  [[nodiscard]] virtual std::function<void(Node *)> appendChildFun() = 0;
};

}

#endif //CAS_SRC_TREE_DFSITERINTERFACE_H
