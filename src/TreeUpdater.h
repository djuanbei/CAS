//
// Created by yun dai on 2024/9/20.
//

#ifndef CAS_SRC_UPDATER_H_
#define CAS_SRC_UPDATER_H_
#include "Node.h"
#include <vector>
#include <memory>
namespace cas {
/**
 * Update node by the member of node of member of direct child
 */

class NodeUpdater {

public:
  virtual ~NodeUpdater() = default;

  bool handle(Node *node) const {
    if (isFit(node)) {
      update(node);
      return true;
    }
    return false;
  }
  [[nodiscard]] int getPriority() const {
    return priority;
  }

  virtual bool listenAllKind() const = 0;
  virtual std::vector<int> getListenType() const = 0;

protected:
  virtual bool isFit(const Node *n) const = 0;
  virtual void update(Node *node) const = 0;

  ///large first
  int priority{0};

};

inline static bool operator<(const std::shared_ptr<const NodeUpdater> &lhs,
                             const std::shared_ptr<const NodeUpdater> &rhs) {
  return lhs->getPriority() > rhs->getPriority();

}

void update(Node *root, const std::vector<std::shared_ptr<const NodeUpdater>> &updater_list);

}

#endif //CAS_SRC_UPDATER_H_
