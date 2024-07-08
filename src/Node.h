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


        void addChile(Node *node) {
            child_.emplace_back(node);
        }

        void setValueValidFun(validFun_t fun) {
            value_valid_fun = fun;
        }

        [[nodiscard]]  const std::vector<Node *> getChild() const {
            return child_;
        }

        [[nodiscard]]  int getNodeNum() const;

        [[nodiscard]]  int getLeafNodeNum() const;

        [[nodiscard]]  int getDepth() const;


        std::ostream &dump(std::ostream &out) const override;

        [[nodiscard]] bool valid() const override;


    private:
        int type_{0};
        std::vector<Node *> child_;
        void *value_{nullptr};
        Node *parent_{nullptr};

        validFun_t value_valid_fun{nullptr};


        static int nextId() {
            static int global_id = 0;
            return global_id++;
        }

    };




}


#endif //CAS_NODE_H
