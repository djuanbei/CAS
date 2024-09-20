//
// Created by yun dai on 2024/9/20.
//

#ifndef CAS_SRC_UPDATER_H_
#define CAS_SRC_UPDATER_H_
#include "Node.h"
#include <vector>
#include <memory>
namespace cas {

class NodeUpdater {

 public:
  virtual ~NodeUpdater() = default;
  virtual bool isFit(const Node *n) const = 0;
  virtual void update(Node *node) const = 0;
  virtual bool listenAllKind() const = 0;
  virtual std::vector<int> getListenType() const = 0;

};

void update(Node *root, const std::vector<std::shared_ptr<const NodeUpdater>> &updater_list);

}

#endif //CAS_SRC_UPDATER_H_
