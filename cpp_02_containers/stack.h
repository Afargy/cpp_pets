#ifndef CPP2_S21_CONTAINERS_1_SRC_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_STACK_H_

#include "list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class stack {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 public:
  stack() : container_(){};
  stack(std::initializer_list<value_type> const &items) : container_(items){};
  stack(const stack &other) : container_(other.container_){};
  stack(stack &&other) : container_(std::move(other.container_)){};
  ~stack(){};
  stack &operator=(stack &other) noexcept {
    container_ = other.container_;
    return *this;
  }
  stack &operator=(stack &&other) noexcept {
    container_ = std::move(other.container_);
    return *this;
  }
  const_reference top() { return container_.back(); }
  bool empty() const noexcept { return container_.empty(); }
  size_type size() const noexcept { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  void swap(stack &other) { container_.swap(other.container_); }
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    container_.insert_many_front(args...);
  }

 private:
  Container container_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_STACK_H_
