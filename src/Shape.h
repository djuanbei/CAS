//
// Created by yun dai on 2024/7/6.
//

#ifndef CAS_SHAPE_H
#define CAS_SHAPE_H

#include <iostream>
#include <vector>

namespace cas {

class Shape {
public:
  Shape() = default;

  explicit Shape(int d) : value_({d}) {}

  Shape(std::initializer_list<int> vs) : value_(vs) {}

  explicit Shape(const std::vector<int> &vs) : value_(vs) {}

  void addBack(int d) { value_.push_back(d); }

  void addFront(int d) { value_.insert(value_.begin(), d); }

  [[nodiscard]] bool isScalar() const { return value_.empty(); }

  [[nodiscard]] int getDim() const { return value_.size(); }

  [[nodiscard]] const std::vector<int> &getShape() const { return value_; }

  std::ostream &dump(std::ostream &out) const;

  [[nodiscard]] bool valid() const;

private:
  std::vector<int> value_;
};

} // namespace cas

#endif // CAS_SHAPE_H
