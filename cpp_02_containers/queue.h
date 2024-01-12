#ifndef CPP2_S21_CONTAINERS_1_SRC_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_QUEUE_H_

#include "list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 public:
  queue() : container_(){};
  queue(std::initializer_list<value_type> const &items) : container_(items){};
  queue(const queue &other) : container_(other.container_){};
  queue(queue &&other) : container_(std::move(other.container_)){};
  ~queue(){};
  queue &operator=(queue &other) noexcept {
    container_ = other.container_;
    return *this;
  }
  queue &operator=(queue &&other) noexcept {
    container_ = std::move(other.container_);
    return *this;
  }
  const_reference front() { return container_.front(); }
  const_reference back() { return container_.back(); }
  bool empty() const noexcept { return container_.empty(); }
  size_type size() const noexcept { return container_.size(); }
  void push(const_reference value) { container_.push(); }
  void pop() { container_.pop_front(); }
  void swap(queue &other) { container_.swap(other.container_); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    container_.insert_many_back(args...);
  }

 private:
  Container container_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_QUEUE_H_
