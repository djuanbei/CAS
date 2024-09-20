//
// Created by yun dai on 2024/9/20.
//

#include "TreeUpdater.h"
//
#include <cassert>
#include <unordered_map>

namespace cas {
using namespace std;
void update(Node *root, const std::vector<std::shared_ptr<const NodeUpdater>> &updater_list) {
  assert(root);
  std::vector<shared_ptr<const NodeUpdater> > universal_listener;
  unordered_map<int, std::vector<std::shared_ptr<const NodeUpdater>>> updater_map;
  for (auto &updater : updater_list) {
    if (updater->listenAllKind()) {
      universal_listener.emplace_back(updater);
    } else {
      auto listen_types = updater->getListenType();
      for (auto t : listen_types) {
        updater_map[t].emplace_back(updater);
      }
    }
  }
  std::vector<Node *> all_node;

}
}