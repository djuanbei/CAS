//
// Created by yun dai on 2024/9/20.
//

#include "TreeUpdater.h"
//
#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace cas {
using namespace std;
void update(
    Node *root,
    const std::vector<std::shared_ptr<const NodeUpdater>> &updater_list) {
  assert(root);
  std::vector<shared_ptr<const NodeUpdater>> universal_listener;
  unordered_map<int, std::vector<std::shared_ptr<const NodeUpdater>>>
      updater_map;
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
  std::sort(universal_listener.begin(), universal_listener.end());
  for (auto &e : updater_map) {
    std::sort(e.second.begin(), e.second.end());
  }
  std::vector<Node *> wait_nodes = getAllNode(root);

  for (auto n : wait_nodes) {
    n->setStatus(0);
  }
  while (!wait_nodes.empty()) {
    for (auto n : wait_nodes) {
      auto orig_type = n->getType();
      if (updater_map.find(n->getType()) != updater_map.end()) {
        auto it = updater_map.at(n->getType()).begin();
        auto jt = universal_listener.begin();
        while (n->getType() == orig_type &&
               (it != updater_map.at(orig_type).end()) &&
               (jt != universal_listener.end())) {

          if (it->get()->getPriority() > jt->get()->getPriority()) {
            if (it->get()->handle(n)) {
              n->setStatus(1);
            }
            it++;
          } else {
            if (jt->get()->handle(n)) {
              n->setStatus(1);
            }
            jt++;
          }
        }
        while ((n->getType() == orig_type) &&
               (it != updater_map.at(orig_type).end())) {
          if (it->get()->handle(n)) {
            n->setStatus(1);
          }
          it++;
        }
        while ((n->getType() == orig_type) &&
               (jt != universal_listener.end())) {
          if (jt->get()->handle(n)) {
            n->setStatus(1);
          }
          jt++;
        }
      } else {
        for (auto &u : universal_listener) {
          if (u->handle(n)) {
            n->setStatus(1);
            if (n->getType() != orig_type) {
              break;
            }
          }
        }
      }
    }
    wait_nodes.clear();
    auto nodes = getAllNode(root);
    for (auto n : nodes) {
      if (n->getStatus()) {
        auto p = n->getParent();
        if (p) {
          p->setStatus(1);
        }
      }
    }
    for (auto n : nodes) {
      if (n->getStatus()) {
        wait_nodes.emplace_back(n);
      }
    }
  }
}
} // namespace cas
