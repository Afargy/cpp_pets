#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_MAP_H_

#include <utility>

namespace s21 {

template <typename Key, typename T>
class map {
  template <typename U>
  friend class set;

 private:
  class Node;

 public:
  class TreeIterator;
  class TreeConstIterator;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator;
  using const_iterator = TreeConstIterator;
  using size_type = std::size_t;
  using init_list = std::initializer_list<value_type>;
  using pair_iterator_bool = std::pair<iterator, bool>;

 private:
  class Node {
    friend class map;

   private:
    Node() = default;
    Node(value_type pair_values) : pair_{pair_values} {};
    Node(Node* left, Node* right) : left_{left}, right_{right} {};

   public:
    Node* parent() const noexcept;
    Node* left() const noexcept;
    Node* right() const noexcept;
    const key_type* key() const noexcept;
    mapped_type* value() noexcept;
    void set_parent(Node* node) noexcept;
    void set_left(Node* node) noexcept;
    void set_right(Node* node) noexcept;
    unsigned height() const noexcept;
    bool is_left_kid() const;
    bool is_root() const noexcept;
    Node* brother() const;
    bool operator<(const Node& node) const;
    bool operator>(const Node& node) const;
    bool operator==(const Node& node) const;
    bool is_leaf() const;

   private:
    Node* parent_{this};
    Node* left_{nullptr};
    Node* right_{nullptr};
    unsigned height_{1};
    value_type pair_{key_type(), mapped_type()};
  };

 public:
  class TreeIterator {
    friend class map;
    template <typename U>
    friend class set;

   public:
    TreeIterator() = default;
    TreeIterator(Node* node) : ptr_(node){};

   public:
    iterator& operator++();
    iterator& operator--();
    iterator operator++(int);
    iterator operator--(int);
    iterator operator+(const size_type move);
    iterator operator-(const size_type move);
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    value_type* operator->() const;

    void throw_if_null() const;

   private:
    Node* get_heir_for_plus(Node* node) const noexcept;
    Node* get_heir_for_minus(Node* node) const noexcept;

   private:
    Node* ptr_{nullptr};
  };

 public:
  class TreeConstIterator : public TreeIterator {
    friend class map;

   public:
    TreeConstIterator() = default;
    TreeConstIterator(const iterator& node) : iterator(node){};
    const value_type* operator->() const;

   private:
    Node* ptr_{nullptr};
  };

 public:
  map() = default;
  map(init_list const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(const map&& m) = delete;
  map& operator=(map&& m) noexcept;

 public:
  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

 public:
  iterator begin() const noexcept;
  iterator end() const noexcept;

 public:
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

 public:
  void clear() noexcept;
  pair_iterator_bool insert(const value_type& value);
  pair_iterator_bool insert(const key_type& value, const mapped_type& obj);
  pair_iterator_bool insert_or_assign(const key_type& key,
                                      const mapped_type& obj);
  void erase(iterator pos);
  void swap(map& other) noexcept;
  void merge(map& other);

 public:
  bool contains(const key_type& key) const noexcept;

 private:
  Node* root() const noexcept;
  void set_root(Node* node) noexcept;
  void set_size(size_type size);
  Node* go_left_till_null(Node* node) const noexcept;
  Node* delete_node(Node* node) noexcept;
  pair_iterator_bool search(key_type key) const noexcept;
  void balance(Node* node) noexcept;
  unsigned height(Node* node) const noexcept;
  void fix_height(Node* node) noexcept;
  Node* get_successor(Node* node) const noexcept;
  void rotate_left(Node* node) noexcept;
  void rotate_right(Node* node) noexcept;
  int balance_factor(Node* node) const noexcept;
  Node* get_min() const noexcept;
  Node* get_max() const noexcept;

 private:
  Node* root_{nullptr};
  size_type size_{0};
  Node base_{&base_, &base_};
};

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::Node::parent() const noexcept {
  return parent_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::Node::left() const noexcept {
  return left_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::Node::right() const noexcept {
  return right_;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::Node::set_parent(Node* node) noexcept {
  parent_ = node;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::Node::set_left(Node* node) noexcept {
  left_ = node;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::Node::set_right(Node* node) noexcept {
  right_ = node;
}

template <typename key_type, typename mapped_type>
const key_type* map<key_type, mapped_type>::Node::key() const noexcept {
  return &pair_.first;
}

template <typename key_type, typename mapped_type>
mapped_type* map<key_type, mapped_type>::Node::value() noexcept {
  return &pair_.second;
}

template <typename key_type, typename mapped_type>
unsigned map<key_type, mapped_type>::Node::height() const noexcept {
  return height_;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::Node::is_left_kid() const {
  return parent()->left() == this;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::Node::is_root() const noexcept {
  return this == parent_;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::Node::operator<(const Node& node) const {
  return *key() < *node.key();
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::Node::operator>(const Node& node) const {
  return *key() > *node.key();
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::Node::operator==(const Node& node) const {
  return *key() == *node.key();
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::Node::is_leaf() const {
  return !(left() || right());
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::Node::brother() const {
  if (is_left_kid()) {
    return parent()->right();
  }
  return parent()->left();
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(init_list const& items) {
  for (const value_type& item : items) {
    insert(item);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map& m) {
  iterator a = m.begin();
  iterator b = m.end();
  while (a != b) {
    insert(a.ptr_->pair_);
    ++a;
  }
  insert(a.ptr_->pair_);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map&& m) {
  root_ = std::move(m.root_);
  size_ = m.size_;
  m.size_ = 0;
  m.root_ = nullptr;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::~map() {
  clear();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::map& map<key_type, mapped_type>::operator=(
    map&& m) noexcept {
  std::cout << "test" << std::endl;
  if (root_ != m.root_) {
    clear();
    swap(m);
  }
  return *this;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
  pair_iterator_bool temp = search(key);
  if (!temp.second) {
    throw std::out_of_range("Has no this elem");
  }
  return *temp.first.ptr_->value();
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::operator[](const key_type& key) {
  pair_iterator_bool temp = search(key);
  if (temp.second) {
    return *temp.first.ptr_->value();
  } else {
    return *base_.value();
  }
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() const noexcept {
  if (size()) {
    return get_min();
  }
  return nullptr;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator map<key_type, mapped_type>::end()
    const noexcept {
  if (size()) {
    return get_max();
  }
  return nullptr;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() const noexcept {
  return !size_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() const noexcept {
  return size_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() const noexcept {
  return (size_type)(-1) / sizeof(Node);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() noexcept {
  Node* current{root()};
  if (size()) {
    while (root()) {
      current = go_left_till_null(current);
      if (current->right() != nullptr) {
        current = current->right();
      }
      if (!current->right() && !current->left()) {
        current = delete_node(current);
      }
    }
  }
  set_size(0);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::pair_iterator_bool
map<key_type, mapped_type>::insert(const value_type& value) {
  Node* new_node{new Node(value)};
  bool insertion{true};
  if (empty()) {
    root_ = new_node;
    set_size(++size_);
  } else {
    Node* current{root_};
    Node* parent{nullptr};
    while (current) {
      parent = current;
      if (*new_node > *current) {
        current = current->right();
      } else if (*new_node < *current) {
        current = current->left();
      } else {
        delete new_node;
        new_node = nullptr;
        insertion = false;
        return {parent, insertion};
      }
    }
    if (new_node) {
      new_node->set_parent(parent);
      if (*new_node > *parent) {
        parent->set_right(new_node);
      } else {
        parent->set_left(new_node);
      }
      set_size(++size_);
      balance(new_node);
    }
  }
  return {new_node, insertion};
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::pair_iterator_bool
map<key_type, mapped_type>::insert(const key_type& value,
                                   const mapped_type& obj) {
  return insert({value, obj});
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::pair_iterator_bool
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  pair_iterator_bool pair = insert({key, obj});
  if (!pair.second) {
    at(key) = obj;
  }
  return pair;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  Node* node{pos.ptr_};
  if (!node) return;
  if (node->is_leaf()) {
    Node *brother{nullptr}, *parent{node->parent()};
    if (!node->is_root()) {
      brother = node->brother();
      (node->is_left_kid()) ? node->parent()->set_left(nullptr)
                            : node->parent()->set_right(nullptr);
      balance(node->parent());
    } else {
      set_root(nullptr);
    }
    if (brother) balance(brother);
    balance(parent);
    delete node;
    set_size(--size_);
    return;
  }
  Node* successor{nullptr};
  if (node->right())
    successor = get_successor(node->right());
  else if (node->left())
    successor = get_successor(node->left());
  Node* kid{(successor->left()) ? successor->left() : successor->right()};
  if (kid) kid->set_parent(successor->parent());
  (successor->is_left_kid()) ? successor->parent()->set_left(kid)
                             : successor->parent()->set_right(kid);
  if (node->is_root()) {
    set_root(successor);
    successor->set_parent(successor);
  } else {
    (node->is_left_kid()) ? node->parent()->set_left(successor)
                          : node->parent()->set_right(successor);
    successor->set_parent(node->parent());
  }
  successor->set_right(node->right());
  if (successor->right()) successor->right()->set_parent(successor);
  successor->set_left(node->left());
  if (successor->left()) successor->left()->set_parent(successor);
  delete node;
  --size_;
  balance(successor);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) noexcept {
  (void)other;
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  while (other.size()) {
    insert(other.root_->pair_);
    iterator it(other.root());
    other.erase(it);
  }
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) const noexcept {
  return search(key).second;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node* map<key_type, mapped_type>::root()
    const noexcept {
  return root_;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::set_root(Node* node) noexcept {
  root_ = node;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::set_size(size_type size) {
  if (size > max_size()) {
    std::out_of_range("Size bigger than max_size");
  }
  size_ = size;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::go_left_till_null(Node* node) const noexcept {
  Node* current{node};
  while (current->left()) {
    current = current->left();
  }
  return current;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::delete_node(Node* node) noexcept {
  Node* parent{node->parent()};
  if (node == root()) {
    set_root(nullptr);
  }
  if (parent && node->is_left_kid()) {
    parent->set_left(nullptr);
  } else {
    parent->set_right(nullptr);
  }
  delete node;
  return parent;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::pair_iterator_bool
map<key_type, mapped_type>::search(key_type key) const noexcept {
  Node* current{root()};
  while (current) {
    if (key > *current->key()) {
      current = current->right();
    } else if (key < *current->key()) {
      current = current->left();
    } else {
      return {current, true};
    }
  }
  return {nullptr, false};
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::balance(Node* node) noexcept {
  while (!node->is_root()) {
    fix_height(node);
    int balance = balance_factor(node);
    if (balance > 1) {
      if (node->right() && balance_factor(node->right()) < 0) {
        rotate_left(node);
        node = node->parent();
      }
      rotate_right(node->parent());
    } else if (balance < -1) {
      if (node->left() && balance_factor(node->left()) > 0) {
        rotate_right(node);
        node = node->parent();
      }
      rotate_left(node->parent());
    }
    node = node->parent();
  }
  fix_height(node);
}

template <typename key_type, typename mapped_type>
unsigned map<key_type, mapped_type>::height(Node* node) const noexcept {
  return node ? node->height_ : 0;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::fix_height(Node* node) noexcept {
  unsigned left_height = height(node->left_);
  unsigned right_height = height(node->right_);
  node->height_ = (left_height > right_height ? left_height : right_height) + 1;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::get_successor(Node* node) const noexcept {
  Node* current{node};
  if (node->is_left_kid()) {
    while (current->right_ != nullptr) {
      current = current->right_;
    }
  } else {
    while (current->left_ != nullptr) {
      current = current->left_;
    }
  }
  return current;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rotate_left(Node* node) noexcept {
  Node* right{node->right()};
  Node* successor{right->left()};
  if (node->is_root()) {
    set_root(right);
    right->set_parent(right);
  } else {
    Node* parent{node->parent()};
    if (node->is_left_kid()) {
      parent->set_left(right);
    } else {
      parent->set_right(right);
    }
    right->set_parent(parent);
  }
  right->set_left(node);
  node->set_parent(right);
  node->set_right(successor);
  if (successor) {
    successor->set_parent(node);
  }
  fix_height(node);
  fix_height(right);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::rotate_right(Node* node) noexcept {
  Node* left{node->left()};
  Node* successor{left->right()};
  if (node->is_root()) {
    set_root(left);
    left->set_parent(left);
  } else {
    Node* parent{node->parent()};
    if (node->is_left_kid()) {
      parent->set_left(left);
    } else {
      parent->set_right(left);
    }
    left->set_parent(parent);
  }
  left->set_right(node);
  node->set_parent(left);
  node->set_left(successor);
  if (successor) {
    successor->set_parent(node);
  }
  fix_height(node);
  fix_height(left);
}

template <typename key_type, typename mapped_type>
int map<key_type, mapped_type>::balance_factor(Node* node) const noexcept {
  if (node->is_root()) {
    return 0;
  }
  if (node->is_left_kid()) {
    return height(node) - height((node->brother()));
  }
  return height((node->brother())) - height(node);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node* map<key_type, mapped_type>::get_min()
    const noexcept {
  if (!size()) {
    return nullptr;
  }
  Node* current{root()};
  while (current->left()) {
    current = current->left();
  }
  return current;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node* map<key_type, mapped_type>::get_max()
    const noexcept {
  if (!size()) {
    return nullptr;
  }
  Node* current{root()};
  while (current->right()) {
    current = current->right();
  }
  return current;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator&
map<key_type, mapped_type>::TreeIterator::operator++() {
  throw_if_null();
  if (ptr_->right()) {
    ptr_ = get_heir_for_plus(ptr_->right());
    return *this;
  }
  Node* origin{ptr_};
  Node* current{ptr_};
  while (*current < *origin || *current == *origin) {
    current = current->parent();
    if (current->is_root() &&
        (!current->right() || *current->right() < *origin ||
         *current->right() == *origin)) {
      break;
    }
  }
  if (*current > *origin) {
    ptr_ = current;
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator&
map<key_type, mapped_type>::TreeIterator::operator--() {
  throw_if_null();
  if (ptr_->left()) {
    ptr_ = get_heir_for_minus(ptr_->left());
    return *this;
  }
  Node* origin{ptr_};
  Node* current{ptr_};
  while (*current > *origin || *current == *origin) {
    current = current->parent();
    if (current->is_root() && (!current->left() || *current->left() > *origin ||
                               *current->left() == *origin)) {
      break;
    }
  }
  if (*current < *origin) {
    ptr_ = current;
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::TreeIterator::operator++(int) {
  throw_if_null();
  iterator temp{*this};
  ++(*this);
  return temp;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::TreeIterator::operator--(int) {
  throw_if_null();
  iterator temp{*this};
  --(*this);
  return temp;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::TreeIterator::operator+(const size_type move) {
  throw_if_null();
  for (size_type i = 0; i < move; ++i) {
    ++*this;
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::TreeIterator::operator-(const size_type move) {
  throw_if_null();
  for (size_type i = 0; i < move; ++i) {
    --*this;
  }
  return *this;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::TreeIterator::operator==(
    const iterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::TreeIterator::operator!=(
    const iterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::value_type*
map<key_type, mapped_type>::TreeIterator::operator->() const {
  throw_if_null();
  return &ptr_->pair_;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::TreeIterator::throw_if_null() const {
  if (ptr_ == nullptr) {
    throw std::out_of_range("Operation with null iterator");
  }
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::TreeIterator::get_heir_for_plus(
    Node* node) const noexcept {
  Node* current{node};
  while (current->left_ != nullptr) {
    current = current->left_;
  }
  return current;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::TreeIterator::get_heir_for_minus(
    Node* node) const noexcept {
  Node* current{node};
  while (current->right_ != nullptr) {
    current = current->right_;
  }
  return current;
}

template <typename key_type, typename mapped_type>
const typename map<key_type, mapped_type>::value_type*
map<key_type, mapped_type>::TreeConstIterator::operator->() const {
  return iterator::operator->();
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_H_
