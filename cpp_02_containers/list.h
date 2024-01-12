#ifndef CPP2_S21_CONTAINERS_1_SRC_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_LIST_H_

#include <stdexcept>

namespace s21 {
template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;
  using init_list = std::initializer_list<T>;

  class Node {
    friend class list;

   private:
    Node(value_type value) : value_{value} {};
    Node* prev_{this};
    Node* next_{this};
    value_type value_{value_type()};
  };

 public:
  class ListIterator {
    friend class list;

   public:
    ListIterator() = default;
    ListIterator(Node* ptr) : current_(ptr){};
    iterator& operator++();
    iterator& operator--();
    iterator operator++(int);
    iterator operator--(int);
    iterator operator+(const size_t move);
    iterator operator-(const size_t move);
    bool operator==(const iterator& other) const noexcept;
    bool operator!=(const iterator& other) const noexcept;
    reference operator*() const;

   private:
    void throw_if_null() const;

   private:
    Node* current_{nullptr};
  };

  class ListConstIterator : public iterator {
   public:
    ListConstIterator() = default;
    ListConstIterator(const iterator& node) : iterator(node){};
    const_reference operator*() const;
  };

 public:
  list() = default;
  list(const size_type size);
  list(init_list const& items);
  list(const list& other);
  list(list&& other);
  ~list();
  list& operator=(list& other) noexcept;
  list& operator=(list&& other) noexcept;

 public:
  const_reference front();
  const_reference back();

 public:
  iterator begin() noexcept;
  iterator end() noexcept;

 public:
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

 public:
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const value_type value);
  void push_front(const value_type value);
  void pop_back();
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse() noexcept;
  void unique();
  void sort() noexcept;

 public:
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  void throw_if_empty() const;

 private:
  Node base_{0};
  Node* end_{&base_};
  size_type size_{0};
};

template <typename value_type>
list<value_type>::list(const size_type size) : list() {
  for (size_type i = 0; i < size; ++i) {
    push_back(0);
  }
}

template <typename value_type>
list<value_type>::list(init_list const& items) : list() {
  for (const value_type item : items) {
    push_back(item);
  }
}

template <typename value_type>
list<value_type>::list(const list& other) {
  Node* current = other.end_->next_;
  for (size_type i = 0; i < other.size_; ++i) {
    push_back(current->value_);
    current = current->next_;
  }
}

template <typename value_type>
list<value_type>::list(list&& other) {
  swap(other);
}

template <typename value_type>
list<value_type>::~list() {
  clear();
}

template <typename value_type>
typename list<value_type>::list& list<value_type>::operator=(
    list& other) noexcept {
  if (end_ != other.end_) {
    clear();
    Node* current = other.end_->next_;
    for (size_type i = 0; i < other.size_; ++i) {
      push_back(current->value_);
      current = current->next_;
    }
  }
  return *this;
}

template <typename value_type>
typename list<value_type>::list& list<value_type>::operator=(
    list&& other) noexcept {
  if (end_ != other.end_) {
    clear();
    swap(other);
  }
  return *this;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  throw_if_empty();
  return end_->next_->value_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  throw_if_empty();
  return end_->prev_->value_;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() noexcept {
  return iterator(end_->next_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() noexcept {
  return iterator(end_);
}

template <typename value_type>
bool list<value_type>::empty() const noexcept {
  return !size_;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() const noexcept {
  return size_;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size()
    const noexcept {
  return (size_t)(-1) / sizeof(Node) / 2;
}

template <typename value_type>
void list<value_type>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  pos.throw_if_null();
  Node* current = pos.current_;
  Node* new_node = new Node(value);
  std::swap(new_node->next_, current->prev_->next_);
  std::swap(new_node->prev_, current->prev_);
  ++size_;
  return new_node;
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  throw_if_empty();
  pos.throw_if_null();
  Node* current = pos.current_;
  if (current == end_) {
    throw std::out_of_range("Erase end");
  } else {
    Node* temp = current->prev_;
    std::swap(temp->next_, current->next_);
    std::swap(temp->next_->prev_, current->prev_);
    delete current;
    --size_;
  }
}

template <typename value_type>
void list<value_type>::push_back(const value_type value) {
  Node* new_node = new Node(value);
  std::swap(new_node->prev_, end_->prev_);
  std::swap(new_node->next_, new_node->prev_->next_);
  ++size_;
}

template <typename value_type>
void list<value_type>::push_front(const value_type value) {
  Node* new_node = new Node(value);
  std::swap(new_node->next_, end_->next_);
  std::swap(new_node->prev_, new_node->next_->prev_);
  ++size_;
}

template <typename value_type>
void list<value_type>::pop_back() {
  throw_if_empty();
  Node* temp = end_->prev_;
  std::swap(temp->next_, temp->prev_->next_);
  std::swap(temp->prev_, end_->prev_);
  delete temp;
  --size_;
}

template <typename value_type>
void list<value_type>::pop_front() {
  throw_if_empty();
  Node* temp = end_->next_;
  std::swap(temp->prev_, temp->next_->prev_);
  std::swap(temp->next_, end_->next_);
  delete temp;
  --size_;
}

template <typename value_type>
void list<value_type>::swap(list& other) noexcept {
  if ((empty() && other.empty()) || (end_ == other.end_)) {
    return;
  } else if (empty()) {
    end_->next_ = other.end_->next_;
    end_->prev_ = other.end_->prev_;
    other.end_->next_->prev_ = end_;
    other.end_->prev_->next_ = end_;
    other.end_->next_ = other.end_;
    other.end_->prev_ = other.end_;
  } else if (other.empty()) {
    other.end_->next_ = end_->next_;
    other.end_->prev_ = end_->prev_;
    end_->next_->prev_ = other.end_;
    end_->prev_->next_ = other.end_;
    end_->next_ = end_;
    end_->prev_ = end_;
  } else {
    end_->next_->prev_ = other.end_;
    end_->prev_->next_ = other.end_;
    other.end_->next_->prev_ = end_;
    other.end_->prev_->next_ = end_;
    Node* head = other.end_->next_;
    Node* tail = other.end_->prev_;
    other.end_->next_ = end_->next_;
    other.end_->prev_ = end_->prev_;
    end_->next_ = head;
    end_->prev_ = tail;
  }
  std::swap(size_, other.size_);
}

template <typename value_type>
void list<value_type>::merge(list& other) {
  if (end_ == other.end_ || other.empty()) {
    return;
  }
  iterator iter_this = begin();
  iterator iter_other = other.begin();
  while (iter_this != end() && iter_other != other.end()) {
    if (iter_this.current_->value_ > iter_other.current_->value_) {
      insert(iter_this, iter_other.current_->value_);
      ++iter_other;
    } else {
      ++iter_this;
    }
  }
  while (iter_other != other.end()) {
    insert(iter_this, iter_other.current_->value_);
    ++iter_other;
  }
  other.clear();
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
  if (end_ == other.end_) {
    throw std::logic_error("Insert list into the same list");
  }
  if (other.empty()) {
    return;
  }
  Node* insert_after = pos.current_->prev_;
  Node* insert_before = pos.current_;
  Node* other_head = other.end_->next_;
  Node* other_tail = other.end_->prev_;
  other_head->prev_ = insert_after;
  insert_after->next_ = other_head;
  other_tail->next_ = insert_before;
  insert_before->prev_ = other_tail;
  size_ += other.size_;
  other.size_ = 0;
  other.end_->prev_ = other.end_;
  other.end_->next_ = other.end_;
}

template <typename value_type>
void list<value_type>::reverse() noexcept {
  Node* temp = end_;
  for (size_type i = 0; i < size_ + 1; ++i) {
    std::swap(temp->next_, temp->prev_);
    temp = temp->prev_;
  }
}

template <typename value_type>
void list<value_type>::unique() {
  Node* current = end_->next_;
  while (current != end_) {
    if (current->value_ == current->next_->value_) {
      erase(current->next_);
    } else {
      current = current->next_;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() noexcept {
  if (empty()) {
    return;
  }
  for (size_type i = 0, edge = size_ - 1; i < edge; ++i) {
    Node* temp = end_->next_;
    for (size_type j = 0; j < edge - i; ++j) {
      if (temp->value_ > temp->next_->value_) {
        std::swap(temp->value_, temp->next_->value_);
      }
      temp = temp->next_;
    }
  }
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  for (const_reference& arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args&&... args) {
  for (const_reference& arg : {args...}) {
    push_back(arg);
  }
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args&&... args) {
  iterator iter = begin();
  for (const_reference& arg : {args...}) {
    insert(iter, arg);
  }
}

template <typename value_type>
void list<value_type>::throw_if_empty() const {
  if (empty()) {
    throw std::out_of_range("The list is empty");
  }
}

template <typename value_type>
typename list<value_type>::iterator& list<value_type>::iterator::operator++() {
  throw_if_null();
  current_ = current_->next_;
  return *this;
}

template <typename value_type>
typename list<value_type>::iterator& list<value_type>::iterator::operator--() {
  throw_if_null();
  current_ = current_->prev_;
  return *this;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::iterator::operator++(
    int) {
  throw_if_null();
  iterator temp = *this;
  current_ = current_->next_;
  return temp;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::iterator::operator--(
    int) {
  throw_if_null();
  iterator temp = current_;
  current_ = current_->prev_;
  return temp;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::iterator::operator+(
    const size_type move) {
  throw_if_null();
  for (size_type i = 0; i < move; ++i) {
    ++*this;
  }
  return *this;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::iterator::operator-(
    const size_type move) {
  throw_if_null();
  for (size_type i = 0; i < move; ++i) {
    --*this;
  }
  return *this;
}

template <typename value_type>
bool list<value_type>::iterator::operator==(
    const iterator& other) const noexcept {
  return current_ == other.current_;
}

template <typename value_type>
bool list<value_type>::iterator::operator!=(
    const iterator& other) const noexcept {
  return current_ != other.current_;
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::iterator::operator*()
    const {
  throw_if_null();
  return current_->value_;
}

template <typename value_type>
typename list<value_type>::const_reference
list<value_type>::const_iterator::operator*() const {
  return iterator::operator*();
}

template <typename value_type>
void list<value_type>::iterator::throw_if_null() const {
  if (current_ == nullptr) {
    throw std::out_of_range("Operation with null iterator");
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_LIST_H_
