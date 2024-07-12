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

    typedef std::ostream &(*dumpFun_t)(std::ostream &, int tab_indent, const void *);


    class Node : public IDMiXin<Node>, public DumpAble, public ValidAble {
    public:
        Node(const Node &) = delete;

        Node(Node &&) = delete;

        Node &operator=(const Node &n) = delete;

        const void *getValue() const {
            return value_;
        }

        uint64_t getStatus() const {
            return status_;
        }


        void addChild(Node *node) {
            child_.emplace_back(node);
        }

        void setValueValidFun(validFun_t fun) {
            value_valid_fun = fun;
        }

        void setValueDumpDun(dumpFun_t fun) {
            value_dump_fun = fun;
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
            if (id >= child_.size()) {
                return nullptr;
            }
            return child_[id];
        }

        [[nodiscard]]  int getNodeNum() const;

        [[nodiscard]]  int getLeafNodeNum() const;

        [[nodiscard]]  int getDepth() const;

        friend Node *createNode();

        friend Node *createNode(void *v);


        std::ostream &dump(std::ostream &out, int tab_indent = 0) const override;

        [[nodiscard]] bool valid() const override;


    private:
        Node() = default;

        Node(void *v) : value_(v) {

        }

        int type_{0};
        std::vector<Node *> child_;
        uint64_t status_{0};
        void *value_{nullptr};
        Node *parent_{nullptr};

        validFun_t value_valid_fun{nullptr};
        dumpFun_t value_dump_fun{nullptr};


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
            if (ch_index < 0) {
                return node;
            }
            return node->getChild(ch_index);
        }

        bool withNextSlide() const {
            return ch_index + 1 < node->getChildNum();
        }

        Node *node{nullptr};
        int ch_index{0};


    };

///DFS
    class NodeDFSIter {

    public:
        explicit NodeDFSIter(Node *root) {
            index_seq.emplace_back(root, -2);
        }

        bool next();

        Node *getCurrentNode() {
            return index_seq.back().getCurrentNode();
        }

        void nextSlide();

        void downChild();

        void upParent();

    private:

        std::vector<NodeIt> index_seq;

    };


    struct ConstDFSNodeIt {
        ConstDFSNodeIt() = default;

        ConstDFSNodeIt(const Node *n, int i) : node(n), ch_index(i) {

        }

        const Node *getCurrentNode() const {
            return node->getChild(ch_index);
        }

        bool withNextSlide() const {
            return ch_index + 1 < node->getChildNum();
        }


        const Node *node{nullptr};
        int ch_index{0};
    };

    class ConstDFSNodeIter {

    public:

        explicit ConstDFSNodeIter(Node *root) {
            index_seq.emplace_back(root, -2);
        }

        void nextSlide();

        void downChild();

        void upParent();


        bool next();

        [[nodiscard]] const Node *getCurrentNode() const {
            return index_seq.back().getCurrentNode();
        }


    private:
        std::vector<ConstDFSNodeIt> index_seq;
    };

    Node *createNode();

    Node *createNode(void *v);


}


#endif //CAS_NODE_H
