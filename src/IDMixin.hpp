//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_IDMIXIN_H
#define CAS_IDMIXIN_H

#include <type_traits>

namespace cas {

template <typename D> class IDMiXin {
public:
  IDMiXin() {
    static_assert(std::is_base_of<IDMiXin<D>, D>::value);
    id_ = nextId();
  }

  [[nodiscard]] int getId() const { return id_; }

private:
  int id_{0};

  static int nextId() {
    static int global_id = 0;
    return global_id++;
  }
};

} // namespace cas

#endif // CAS_IDMIXIN_H
