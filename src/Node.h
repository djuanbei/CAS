//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_NODE_H
#define CAS_NODE_H

#include <vector>
#include <memory>
#include "IDMixin.hpp"
#include "ValidAble.h"
#include "DumpAble.h"

namespace cas {


    typedef bool (*validFun_t)(int, void *);

    class Node : public IDMiXin<Node>, public DumpAble, public ValidAble {
    public:
        Node(const Node &) = delete;

        Node(Node &&) = delete;

        Node &operator=(const Node &n) = delete;

        uint64_t getStatus() const {
            return status_;
        }


        void addChile(Node *node) {
            child_.emplace_back(node);
        }

        void setValueValidFun(validFun_t fun) {
            value_valid_fun = fun;
        }

        [[nodiscard]]  const std::vector<Node *> getChild() const {
            return child_;
        }

        int getChildNum() const {
            return child_.size();
        }

        const Node *getChild(int id) const {
            return child_[id];
        }

        Node *getChild(int id) {
            return child_[id];
        }

        [[nodiscard]]  int getNodeNum() const;

        [[nodiscard]]  int getLeafNodeNum() const;

        [[nodiscard]]  int getDepth() const;


        std::ostream &dump(std::ostream &out) const override;

        [[nodiscard]] bool valid() const override;


    private:
        int type_{0};
        std::vector<Node *> child_;
        uint64_t status_{0};
        void *value_{nullptr};
        Node *parent_{nullptr};

        validFun_t value_valid_fun{nullptr};


        static int nextId() {
            static int global_id = 0;
            return global_id++;
        }

    };

    struct NodeIt {
        NodeIt() = default;

        NodeIt(Node *n, int i) : node(n), ch_index(i) {

        }

        Node *getCurrentNode() {
            return node->getChild(ch_index);
        }

        Node *node{nullptr};
        int ch_index{0};
    };

///DFS
    class NodeIter {

    public:
        NodeIter(Node *root) {
            index_seq.emplace_back(root, -1);
        }

        bool next() {
            index_seq.back().ch_index++;
            while (true) {
                if (index_seq.size() == 1 && index_seq[0].ch_index >= index_seq[0].node->getChildNum()) {
                    return false;
                }
                if (index_seq.back().ch_index >= index_seq.back().node->getChildNum()) {
                    index_seq.pop_back();
                    continue;
                }
                return true;
            }
            return false;
        }

        Node *getCurrentNode() {
            return index_seq.back().getCurrentNode();
        }

    private:

        std::vector<NodeIt> index_seq;

    };


    struct Const_NodeIt {
        Const_NodeIt() = default;

        Const_NodeIt(const Node *n, int i) : node(n), ch_index(i) {

        }

        const Node *getCurrentNode() const {
            return node->getChild(ch_index);
        }

        const Node *node{nullptr};
        int ch_index{0};
    };

    class Const_NodeIter {

    public:
        const Node *getCurrentNode() const {
            return index_seq.back().getCurrentNode();
        }


    private:
        std::vector<Const_NodeIt> index_seq;
    };


}


#endif //CAS_NODE_H
