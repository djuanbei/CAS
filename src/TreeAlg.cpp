//
// Created by yun dai on 2024/7/9.
//
#include "TreeAlg.h"
#include "Node.h"
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>
#include <iostream>

namespace cas {
    using namespace std;

    namespace {
        Node *build(const std::vector<int> &value, int &i, int level, int degree) {
            assert(level > 0);
            assert(i < value.size());
            level--;
            auto v = new int;
            *v = value[i++];
            auto re = createNode(v);
            if (level > 0) {
                for (int d = 0; d < degree && i < value.size(); d++) {
                    re->addChild(build(value, i, level, degree));
                }
            }
            auto dump = [](std::ostream &out, int tab_indent, const void *v) -> std::ostream & {
                return out << string(tab_indent, '\t') <<", value: "<< (*((int *) v));
            };
            re->setValueDumpDun(dump);

            return re;


        }
    }

    Node *generateTree(int node_num, int degree, int depth) {
        assert(node_num > 0);
        assert(degree > 0);
        assert(depth > 0);
        assert(depth < 6);
        assert(degree < 5);
        std::vector<int> node_value(node_num);
        for (size_t i = 0; i < node_value.size(); i++) {
            node_value[i] = i;
        }
        shuffle(node_value.begin(), node_value.end(), std::default_random_engine());

        int i = 0;
        return build(node_value, i, depth, degree);

    }


    void dfs(const Node *node, nodeCheck_t is_ok, handle_fun_t fun) {
        assert(node);
        if (is_ok(node)) {
            fun(node);
        }
        if (node->getChildNum() == 0) {
            return;
        }
//
//        ConstDFSNodeIter nodeIter(node);
//        nodeIter.index_seq.emplace_back(node, 0);
//
//        while ((nodeIter.index_seq.back().node != node) ||
//               (nodeIter.index_seq.back().ch_index != node->getChildNum())) {
//
//
//        }

    }

}