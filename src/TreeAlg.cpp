//
// Created by yun dai on 2024/7/9.
//
#include "TreeAlg.h"
#include <cassert>

namespace cas {


    void dfs(const Node *node, nodeCheck_t is_ok, handle_fun_t fun) {
        assert(node);
        if (is_ok(node)) {
            fun(node);
        }
        if (node->getChildNum() == 0) {
            return;
        }
        Const_NodeIter nodeIter;
        nodeIter.index_seq.emplace_back(node, 0);

        while ((nodeIter.index_seq.back().node != node) ||
               (nodeIter.index_seq.back().ch_index != node->getChildNum())) {


        }

    }

}