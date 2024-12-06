//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_MEMORY_H
#define CAS_MEMORY_H

#include <cassert>
#include <vector>
//
#include "IDMixin.hpp"
#include "ValidAble.h"

namespace cas {

class Memory : public IDMiXin<Memory> {

public:
  enum MEMORY_KIND { FLOAT32_T, FLOAT64_T, INT32_T };

  explicit Memory(size_t len) : length_(len) {}

  Memory(MEMORY_KIND kind, size_t len) : length_(len), memory_kind_(kind) {}

  [[nodiscard]] MEMORY_KIND getKind() const { return memory_kind_; }

  [[nodiscard]] size_t getLen() const { return length_; }

private:
  size_t length_{0};
  MEMORY_KIND memory_kind_{FLOAT64_T};
};

/**
 * [start_, end_)
 */
class MemSeg : public ValidAble {
public:
  MemSeg() = default;

  MemSeg(int m_id, size_t s, size_t e) : m_id_(m_id), start_(s), end_(e) {}

  [[nodiscard]] int getMemId() const {
    assert(valid());
    return m_id_;
  }

  void setMemId(int id) {
    assert(valid());
    m_id_ = id;
    assert(valid());
  }

  void setStart(size_t s) { start_ = s; }

  void setEnd(size_t e) { end_ = e; }

  void setRange(size_t s, size_t e) {
    assert(valid());
    start_ = s;
    end_ = e;
    assert(valid());
  }

  [[nodiscard]] size_t getStart() const {
    assert(valid());
    return start_;
  }

  [[nodiscard]] size_t getEnd() const {

    assert(valid());
    return end_;
  }

  [[nodiscard]] size_t getLen() const {
    assert(valid());
    return end_ - start_;
  }

  [[nodiscard]] bool isEmpty() const { return end_ == start_; }

  [[nodiscard]] bool valid() const override {
    return (m_id_ >= 0) && (end_ >= start_);
  }

private:
  int m_id_{0};
  size_t start_{0}, end_{0};
};

class MemSet : public ValidAble {

private:
  std::vector<MemSeg> segments_;
};
} // namespace cas

#endif // CAS_MEMORY_H
