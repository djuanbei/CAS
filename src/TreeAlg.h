//
// Created by yun dai on 2024/7/8.
//

#ifndef CAS_TREEALG_H
#define CAS_TREEALG_H

#include "Node.h"

namespace cas {


    typedef bool (*nodeCheck_t)(const Node *);

    typedef void (*handle_fun_t)(const Node *);

    typedef void (*modify_fun_t)(Node *);

    typedef double (*weight_fun_t)(const Node *);

    void dfs(const Node *node, nodeCheck_t is_ok, handle_fun_t fun);

    void dfs(Node *node, nodeCheck_t is_ok, modify_fun_t fun);

    void bfs(const Node *node, nodeCheck_t is_ok, handle_fun_t fun);

    void bfs(Node *node, nodeCheck_t is_ok, modify_fun_t fun);

    void priorityFirst(const Node *node, nodeCheck_t is_ok, weight_fun_t w_fun, handle_fun_t fun);

    void priorityFirst(Node *node, nodeCheck_t is_ok, weight_fun_t w_fun, modify_fun_t fun);


}

#endif //CAS_TREEALG_H
