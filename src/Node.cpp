//
// Created by yun dai on 2024/7/8.
//

#include "Node.h"
#include <cassert>

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


    bool NodeIter::next() {

        if (index_seq.empty()) {
            return false;
        }

        auto current = getCurrentNode();
        assert(current);

        if (current->getChildNum() > 0) {
            index_seq.emplace_back(current->getChild(0), -1);
            return true;
        }

        index_seq.back().ch_index++;

        auto next_node = getCurrentNode();

        while (next_node == nullptr) {
            index_seq.pop_back();
            if (index_seq.empty()) {
                return false;
            }
            index_seq.back().ch_index++;
            next_node = getCurrentNode();
        }
        index_seq.emplace_back(next_node, -1);

        return true;


    }

    bool Const_NodeIter::next() {
        if (index_seq.empty()) {
            return false;
        }

        auto current = getCurrentNode();
        assert(current);

        if (current->getChildNum() > 0) {
            index_seq.emplace_back(current->getChild(0), -1);
            return true;
        }

        index_seq.back().ch_index++;

        auto next_node = getCurrentNode();

        while (next_node == nullptr) {
            index_seq.pop_back();
            if (index_seq.empty()) {
                return false;
            }
            index_seq.back().ch_index++;
            next_node = getCurrentNode();
        }
        index_seq.emplace_back(next_node, -1);

        return true;


    }


}
