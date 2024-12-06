//
// Created by yun dai on 2024/9/21.
//

#include "EnumBitDFSIter.h"
#include <cassert>
#include <vector>
namespace cas {
using namespace std;
EnumBitDFSIter::EnumBitDFSIter(int len) : N(len) {
  assert(len > 0);
  auto des_fun = [](void *v) {
    delete ((std::vector<int> *) (v));
  };
  node_manager.setValueDesFun(des_fun);
  auto vv = new std::vector<int>();
  /// index start 0 is dummy value;
  vv->emplace_back(0);
  root = node_manager.createNode(vv);
}


}