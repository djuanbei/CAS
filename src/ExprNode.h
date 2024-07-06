//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_EXPRNODE_H
#define CAS_EXPRNODE_H

#include <vector>
#include <memory>

namespace cas {

    class ExprNode {
    public:
        ExprNode() {
            id_ = nextId();
        }

        [[nodiscard]] int getId() const {
            return id_;
        }

        void addChild(const ExprNode &node) {
            child_.emplace_back(std::make_shared<ExprNode>(node));
        }

        void addChild(const std::shared_ptr<const ExprNode> &node) {
            child_.emplace_back(node);
        }

        [[nodiscard]]  const std::vector<std::shared_ptr<const ExprNode>> getChild() const {
            return child_;
        }

    private:
        int type_{0};
        int id_{0};
        std::vector<std::shared_ptr<const ExprNode> > child_;
        void *value_{nullptr};

        static int nextId() {
            static int global_id = 0;
            return global_id++;
        }

    };

}


#endif //CAS_EXPRNODE_H
