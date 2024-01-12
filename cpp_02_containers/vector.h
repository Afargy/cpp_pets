#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_H_

#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;
  using size_type = std::size_t;
  using init_list = std::initializer_list<value_type>;
  using pointer = value_type *;

 public:
  class VectorIterator {
    friend class vector;

   public:
    VectorIterator() = default;
    VectorIterator(value_type *ptr) : ptr_(ptr){};

   public:
    iterator &operator++();
    iterator &operator--();
    iterator operator++(int);
    iterator operator--(int);
    iterator operator+(const size_type move);
    iterator operator-(const size_type move);
    iterator operator+=(const size_type move);
    iterator operator-=(const size_type move);
    bool operator==(const iterator &other) const noexcept;
    bool operator!=(const iterator &other) const noexcept;
    reference operator*() const;

   private:
    void throw_if_null() const;

   private:
    pointer ptr_{nullptr};
  };

 public:
  class VectorConstIterator : public iterator {
   public:
    VectorConstIterator() = default;
    VectorConstIterator(const pointer ptr) : iterator(ptr){};
    const_reference operator*() const;
  };

 public:
  vector() = default;
  vector(size_type n);
  vector(init_list const &items);
  vector(const vector &other);
  vector(vector &&other);
  ~vector();
  vector<value_type> &operator=(const vector &other);
  vector<value_type> &operator=(vector &&other) noexcept;

 public:
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  pointer data() noexcept;

 public:
  iterator begin() noexcept;
  iterator end() noexcept;

 public:
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

 public:
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back() noexcept;
  void swap(vector &other) noexcept;
  void resize(size_type count);

 private:
  value_type *container_{nullptr};
  size_type size_{0};
  size_type capacity_{0};
};

template <typename value_type>
vector<value_type>::vector(size_type n) {
  if (n > max_size()) {
    throw std::length_error("New cap is bigger than max_size");
  }
  container_ = new value_type[n]();
  size_ = n;
  capacity_ = n;
}

template <typename value_type>
vector<value_type>::vector(init_list const &items) {
  size_ = items.size();
  if (size_) {
    capacity_ = size_;
    container_ = new value_type[size_]();
    std::copy(items.begin(), items.end(), container_);
  }
}

template <typename value_type>
vector<value_type>::vector(const vector &other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  if (size_) {
    container_ = new value_type[capacity_];
    std::copy(&other.container_[0], &other.container_[size_], container_);
  }
}

template <typename value_type>
vector<value_type>::vector(vector &&other) {
  swap(other);
}

template <typename value_type>
vector<value_type>::~vector() {
  if (capacity_) {
    delete[] container_;
  }
  size_ = 0;
  capacity_ = 0;
  container_ = nullptr;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(const vector &other) {
  this->~vector();
  size_ = other.size_;
  capacity_ = other.capacity_;
  container_ = new value_type[capacity_]();
  std::copy(&other.container_[0], &other.container_[size_], container_);
  return *this;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &&other) noexcept {
  this->~vector();
  swap(other);
  return *this;
}

template <typename value_type>
bool vector<value_type>::empty() const noexcept {
  return size_ == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size()
    const noexcept {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size()
    const noexcept {
  return (size_t)(-1) / sizeof(value_type) / 2;
}

template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("New cap is bigger than max_size");
  }
  if (size > capacity_) {
    pointer new_container = new value_type[size]();
    std::copy(&container_[0], &container_[size_], new_container);
    delete[] container_;
    container_ = new_container;
    capacity_ = size;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity()
    const noexcept {
  return capacity_;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (size_ < capacity_) {
    pointer new_container = new value_type[size_]();
    std::copy(&container_[0], &container_[size_], new_container);
    delete[] container_;
    container_ = new_container;
    capacity_ = size_;
  }
}

template <typename value_type>
void vector<value_type>::clear() noexcept {
  size_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  pos.throw_if_null();
  size_type poss = &(*pos) - container_;
  if (poss > size_) {
    throw std::out_of_range("Inserting out of size");
  }
  push_back(value);
  std::copy(&container_[poss], &container_[size_ - 1], &container_[poss + 1]);
  container_[poss] = value;
  return container_ + poss;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  pos.throw_if_null();
  size_type poss = &(*pos) - container_;
  if (!size_ || poss > size_ - 1) {
    throw std::out_of_range("Deletion empty elem");
  }
  std::copy(&container_[poss + 1], &container_[size_], &container_[poss]);
  --size_;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ == capacity_) {
    resize(size_ + 1);
    --size_;
  }
  container_[size_] = value;
  ++size_;
}

template <typename value_type>
void vector<value_type>::pop_back() noexcept {
  if (size_) {
    --size_;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector &other) noexcept {
  std::swap(container_, other.container_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename value_type>
void vector<value_type>::resize(size_type size) {
  if (size > max_size()) {
    throw std::length_error("New cap is bigger than max_size");
  }
  if (size < capacity_) {
    size_ = size;
  } else if (size > capacity_) {
    size_type new_capacity = capacity_ * 2;
    if (new_capacity < size) {
      new_capacity = size;
    } else if (new_capacity > max_size()) {
      new_capacity = size;
    }
    pointer new_container = new value_type[new_capacity]();
    std::copy(&container_[0], &container_[size_], new_container);
    delete[] container_;
    container_ = new_container;
    capacity_ = new_capacity;
    size_ = size;
  }
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Elem doesn't exist");
  } else {
    return container_[pos];
  }
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return container_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  if (!size_) {
    throw std::out_of_range("Empty container");
  } else {
    return container_[0];
  }
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  if (!size_) {
    throw std::out_of_range("Empty container");
  } else {
    return container_[size_ - 1];
  }
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() noexcept {
  return container_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() noexcept {
  return iterator(container_);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() noexcept {
  return iterator(&container_[size_]);
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::iterator::operator*()
    const {
  throw_if_null();
  return *ptr_;
}

template <typename value_type>
void vector<value_type>::iterator::throw_if_null() const {
  if (ptr_ == nullptr) {
    throw std::out_of_range("Operation with null iterator");
  }
}

template <typename value_type>
typename vector<value_type>::iterator &
vector<value_type>::iterator::operator++() {
  throw_if_null();
  ++ptr_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::iterator &
vector<value_type>::iterator::operator--() {
  throw_if_null();
  --ptr_;
  return *this;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator++(
    int) {
  throw_if_null();
  iterator temp(ptr_);
  ++(*this);
  return temp;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator--(
    int) {
  throw_if_null();
  iterator temp(ptr_);
  --(*this);
  return temp;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator+(
    const size_type move) {
  throw_if_null();
  iterator temp{ptr_ + move};
  return temp;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator-(
    const size_type move) {
  throw_if_null();
  iterator temp{ptr_ - move};
  return temp;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator+=(
    const size_type move) {
  throw_if_null();
  ptr_ += move;
  return *this;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::iterator::operator-=(
    const size_type move) {
  throw_if_null();
  ptr_ -= move;
  return *this;
}

template <typename value_type>
bool vector<value_type>::VectorIterator::operator==(
    const iterator &other) const noexcept {
  return ptr_ == other.ptr_;
}

template <typename value_type>
bool vector<value_type>::VectorIterator::operator!=(
    const iterator &other) const noexcept {
  return ptr_ != other.ptr_;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_H_
