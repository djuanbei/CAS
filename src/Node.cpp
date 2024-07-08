//
// Created by yun dai on 2024/7/8.
//

#include "Node.h"

namespace cas {

    int Node::getNodeNum() const {
        int num = 1;
        for (auto &d: child_) {
            num += getNodeNum();
        }
        return num;

    }


    int Node::getLeafNodeNum() const {
        if (child_.empty()) {
            return 1;
        }

        int num = 0;
        for (auto d: child_) {
            num += getLeafNodeNum();
        }
        return num;
    }

    int Node::getDepth() const {

        int level = 0;

        for (auto d: child_) {
            level = std::max(level, d->getDepth());
        }

        return level + 1;
    }

    bool Node::valid() const {
        if (value_valid_fun) {
            if (!value_valid_fun(type_, value_)) {
                return false;
            }
        }

        for (auto d: child_) {
            if (d->parent_ != nullptr) {
                return false;
            }
        }

        return std::all_of(child_.begin(), child_.end(), [](auto &d) {
            return d->valid();
        });
    }

}
