#ifndef CPP2_S21_CONTAINERS_1_SRC_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_SET_H_

#include "map.h"

namespace s21 {

template <typename value_type>
class set {
 public:
  class SetIterator;
  class SetConstIterator;
  // using value_type = T;
  using iterator = SetIterator;
  using reference = value_type&;
  using const_iterator = SetConstIterator;
  using init_list = std::initializer_list<value_type>;
  using size_type = std::size_t;
  using pair_iterator_bool = std::pair<iterator, bool>;
  using node_type = typename map<value_type, value_type>::Node;
  using node_iter = typename map<value_type, value_type>::iterator;

 public:
  class SetIterator : public map<value_type, value_type>::iterator {
    friend class set;

   public:
    SetIterator() = default;
    SetIterator(node_iter it) : it_{it} {};

   public:
    iterator& operator++() {
      ++it_;
      return *this;
    };
    iterator& operator--() {
      --it_;
      return *this;
    };
    iterator operator++(int) {
      node_iter temp{it_};
      ++it_;
      return temp;
    };
    iterator operator--(int) {
      node_iter temp{it_};
      --it_;
      return temp;
    };
    bool operator==(const iterator& other) const { return it_ == other.it_; };
    bool operator!=(const iterator& other) const { return it_ != other.it_; };
    value_type operator*() const { return it_->second; };

   private:
    node_iter it_{nullptr};
  };

 public:
  class SetConstIterator : public SetIterator {
   public:
    SetConstIterator() = default;
    SetConstIterator(node_iter it) : it_{it} {};

   private:
    node_iter it_{nullptr};
  };

 public:
  set() : container_(){};
  set(init_list const& items) {
    for (const value_type& item : items) {
      insert(item);
    }
  };
  set(const set& m) : container_(m.container_){};
  set(set&& m) : container_(std::move(m.container_)){};
  ~set(){};
  set& operator=(const set&& m) = delete;
  set& operator=(set&& m) noexcept { container_ = std::move(m.container_); }

 public:
  iterator begin() const noexcept { return container_.begin(); };
  iterator end() const noexcept { return container_.end(); };

 public:
  bool empty() const noexcept { return container_.empty(); };
  size_type size() const noexcept { return container_.size(); };
  size_type max_size() const noexcept { return container_.max_size(); };

 public:
  void clear() noexcept { container_.clear(); };
  pair_iterator_bool insert(const value_type& value) {
    std::pair<node_iter, bool> pair = container_.insert({value, value});
    return {pair.first, pair.second};
  }
  void erase(iterator pos) { container_.erase(); };
  void swap(set& other) noexcept { container_.swap(); };
  void merge(set& other) { container_.merge(); };

 public:
  iterator find(const value_type& key) const noexcept {
    if (!size()) {
      return container_.begin();
    }
    iterator head{begin()};
    iterator tail{end()};
    while (head != tail && *head != key) {
      ++head;
    }
    if (head == tail && head.it_ != nullptr && *head != key) {
      return node_iter(nullptr);
    }
    return head;
  };
  bool contains(const value_type& key) const noexcept {
    return container_.contains(key);
  };

 private:
  map<value_type, value_type> container_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_SET_H_
