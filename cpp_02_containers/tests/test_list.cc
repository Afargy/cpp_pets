#include <gtest/gtest.h>

#include <list>

#include "../list.h"

namespace s21 {

template <typename value_type>
bool IsEqual(list<value_type> &our, std::list<value_type> &compared);
template <typename value_type>
bool IsEqual(list<value_type> &our, list<value_type> &compared);

class ListTest : public testing::Test {
 protected:
  list<int> l0_;
  list<int> l1_{1};
  list<int> l2_{1, 2};
  list<int> l3_{1, 2, 3};
};

TEST_F(ListTest, DefaultConstructor) {
  std::list<int> stl;
  EXPECT_EQ(l0_.empty(), stl.empty());
}

TEST_F(ListTest, SizeConsructor) {
  list<int> our_1(0);
  std::list<int> stl_1(0);
  EXPECT_TRUE(IsEqual(our_1, stl_1));

  list<int> our_2(1);
  std::list<int> stl_2(1);
  EXPECT_TRUE(IsEqual(our_2, stl_2));

  list<int> our_3(10);
  std::list<int> stl_3(10);
  EXPECT_TRUE(IsEqual(our_3, stl_3));
}

TEST_F(ListTest, ListConstructor) {
  std::list<int> stl_0{};
  EXPECT_TRUE(IsEqual(l0_, stl_0));

  std::list<int> stl_1{1};
  EXPECT_TRUE(IsEqual(l1_, stl_1));

  std::list<int> stl_2{1, 2};
  EXPECT_TRUE(IsEqual(l2_, stl_2));

  std::list<int> stl_3{1, 2, 3};
  EXPECT_TRUE(IsEqual(l3_, stl_3));
}

TEST_F(ListTest, CopyConstructor) {
  list<int> copied_0{l0_};
  EXPECT_TRUE(IsEqual(l0_, copied_0));

  list<int> copied_1{l1_};
  EXPECT_TRUE(IsEqual(l1_, copied_1));

  list<int> copied_2{l2_};
  EXPECT_TRUE(IsEqual(l2_, copied_2));

  list<int> copied_3{l3_};
  EXPECT_TRUE(IsEqual(l3_, copied_3));
}

TEST_F(ListTest, MoveConstructor) {
  list<int> origin_0;
  list<int> moved_0{std::move(origin_0)};
  EXPECT_TRUE(IsEqual(origin_0, l0_));
  EXPECT_TRUE(IsEqual(moved_0, l0_));

  list<int> origin_1{1};
  list<int> moved_1{std::move(origin_1)};
  EXPECT_TRUE(IsEqual(origin_1, l0_));
  EXPECT_TRUE(IsEqual(moved_1, l1_));

  list<int> origin_2{1, 2};
  list<int> moved_2{std::move(origin_2)};
  EXPECT_TRUE(IsEqual(origin_2, l0_));
  EXPECT_TRUE(IsEqual(moved_2, l2_));

  list<int> origin_3{1, 2, 3};
  list<int> moved_3{std::move(origin_3)};
  EXPECT_TRUE(IsEqual(origin_3, l0_));
  EXPECT_TRUE(IsEqual(moved_3, l3_));
}

TEST_F(ListTest, Clear) {
  l0_.clear();
  EXPECT_EQ(l0_.size(), 0);
  l1_.clear();
  EXPECT_EQ(l1_.size(), 0);
  l2_.clear();
  EXPECT_EQ(l2_.size(), 0);
  l3_.clear();
  EXPECT_EQ(l2_.size(), 0);
}

TEST_F(ListTest, CopyOperator) {
  list<int> copied_0{123, 123};
  copied_0 = l0_;
  EXPECT_TRUE(IsEqual(l0_, copied_0));

  list<int> copied_1{123, 123};
  copied_1 = l1_;
  EXPECT_TRUE(IsEqual(l1_, copied_1));

  list<int> copied_2{123, 123};
  copied_2 = l2_;
  EXPECT_TRUE(IsEqual(l2_, copied_2));

  list<int> copied_3{123, 123};
  copied_3 = l3_;
  EXPECT_TRUE(IsEqual(l3_, copied_3));
}

TEST_F(ListTest, MoveOperator) {
  list<int> origin_0;
  list<int> moved_0{123, 123};
  moved_0 = std::move(origin_0);
  EXPECT_TRUE(IsEqual(origin_0, l0_));
  EXPECT_TRUE(IsEqual(moved_0, l0_));

  list<int> origin_1{1};
  list<int> moved_1{123, 123};
  moved_1 = std::move(origin_1);
  EXPECT_TRUE(IsEqual(origin_1, l0_));
  EXPECT_TRUE(IsEqual(moved_1, l1_));

  list<int> origin_2{1, 2};
  list<int> moved_2{123, 123};
  moved_2 = std::move(origin_2);
  EXPECT_TRUE(IsEqual(origin_2, l0_));
  EXPECT_TRUE(IsEqual(moved_2, l2_));

  list<int> origin_3{1, 2, 3};
  list<int> moved_3{123, 123};
  moved_3 = std::move(origin_3);
  EXPECT_TRUE(IsEqual(origin_3, l0_));
  EXPECT_TRUE(IsEqual(moved_3, l3_));
}

TEST_F(ListTest, Front) {
  EXPECT_ANY_THROW(l0_.front());
  EXPECT_EQ(l1_.front(), 1);
  EXPECT_EQ(l2_.front(), 1);
  EXPECT_EQ(l3_.front(), 1);
}

TEST_F(ListTest, Back) {
  EXPECT_ANY_THROW(l0_.back());
  EXPECT_EQ(l1_.back(), 1);
  EXPECT_EQ(l2_.back(), 2);
  EXPECT_EQ(l3_.back(), 3);
}

TEST_F(ListTest, Begin) {
  EXPECT_EQ(*l0_.begin(), 0);
  EXPECT_EQ(*l1_.begin(), 1);
  EXPECT_EQ(*l2_.begin(), 1);
  EXPECT_EQ(*l3_.begin(), 1);
}

TEST_F(ListTest, End) {
  EXPECT_EQ(*l0_.end(), 0);
  EXPECT_EQ(*l1_.end(), 0);
  EXPECT_EQ(*l2_.end(), 0);
  EXPECT_EQ(*l3_.end(), 0);
}

TEST_F(ListTest, Size) {
  EXPECT_EQ(l0_.size(), 0);
  EXPECT_EQ(l1_.size(), 1);
  EXPECT_EQ(l2_.size(), 2);
  EXPECT_EQ(l3_.size(), 3);
}

TEST_F(ListTest, MaxSize) {
  std::list<int> stl_0{};
  std::list<int> stl_1{1};
  std::list<int> stl_2{1, 2};
  std::list<int> stl_3{1, 2, 3};
  EXPECT_EQ(l0_.max_size(), stl_0.max_size());
  EXPECT_EQ(l1_.max_size(), stl_1.max_size());
  EXPECT_EQ(l2_.max_size(), stl_2.max_size());
  EXPECT_EQ(l3_.max_size(), stl_3.max_size());
}

TEST_F(ListTest, Insert) {
  list<int> our;
  our.insert(our.end(), 1);
  EXPECT_TRUE(IsEqual(our, l1_));
  our.insert(our.end(), 2);
  EXPECT_TRUE(IsEqual(our, l2_));
  our.insert(our.end(), 3);
  EXPECT_TRUE(IsEqual(our, l3_));
  list<int>::iterator iter;
  EXPECT_ANY_THROW(our.insert(iter, 1));
}

TEST_F(ListTest, Erase) {
  list<int> our{0, 1, 2, 3};
  list<int>::iterator iter;
  EXPECT_ANY_THROW(our.erase(iter));
  our.erase(our.begin());
  EXPECT_TRUE(IsEqual(our, l3_));
  our.insert(our.begin() + 1, 100);
  our.erase(our.begin() + 1);
  EXPECT_TRUE(IsEqual(our, l3_));
  our.erase(our.end() - 1);
  EXPECT_TRUE(IsEqual(our, l2_));
  our.erase(our.end() - 1);
  EXPECT_TRUE(IsEqual(our, l1_));
  our.erase(our.end() - 1);
  EXPECT_TRUE(IsEqual(our, l0_));
  EXPECT_ANY_THROW(our.erase(our.end() - 1));
  EXPECT_ANY_THROW(l3_.erase(l3_.end()));
}

TEST_F(ListTest, PushBack) {
  list<int> our;
  our.push_back(1);
  EXPECT_TRUE(IsEqual(our, l1_));
  our.push_back(2);
  EXPECT_TRUE(IsEqual(our, l2_));
  our.push_back(3);
  EXPECT_TRUE(IsEqual(our, l3_));
}

TEST_F(ListTest, PushFront) {
  list<int> our_0{};
  our_0.push_front(1);
  EXPECT_TRUE(IsEqual(our_0, l1_));
  list<int> our_1{};
  our_1.push_front(2);
  our_1.push_front(1);
  EXPECT_TRUE(IsEqual(our_1, l2_));
  list<int> our_2{};
  our_2.push_front(3);
  our_2.push_front(2);
  our_2.push_front(1);
  EXPECT_TRUE(IsEqual(our_2, l3_));
}

TEST_F(ListTest, PopBack) {
  list<int> our{1, 2, 3, 4};
  our.pop_back();
  EXPECT_TRUE(IsEqual(our, l3_));
  our.pop_back();
  EXPECT_TRUE(IsEqual(our, l2_));
  our.pop_back();
  EXPECT_TRUE(IsEqual(our, l1_));
  our.pop_back();
  EXPECT_TRUE(IsEqual(our, l0_));
  EXPECT_ANY_THROW(our.pop_back());
}

TEST_F(ListTest, PopFront) {
  list<int> our_0{2, 3};
  l3_.pop_front();
  EXPECT_TRUE(IsEqual(our_0, l3_));
  list<int> our_1{2};
  l2_.pop_front();
  EXPECT_TRUE(IsEqual(our_1, l2_));
  list<int> our_3{};
  l1_.pop_front();
  EXPECT_TRUE(IsEqual(our_3, l1_));
  EXPECT_ANY_THROW(l0_.pop_back());
}

TEST_F(ListTest, Swap) {
  list<int> our_0{};
  list<int> our_1{1};
  our_0.swap(our_1);
  EXPECT_TRUE(IsEqual(our_0, l1_));
  EXPECT_TRUE(IsEqual(our_1, l0_));
  our_0.swap(our_1);
  EXPECT_TRUE(IsEqual(our_0, l0_));
  EXPECT_TRUE(IsEqual(our_1, l1_));
  list<int> our_2{1, 2};
  {
    list<int> our_3{1, 2, 3};
    our_2.swap(our_3);
    EXPECT_TRUE(IsEqual(our_2, l3_));
    EXPECT_TRUE(IsEqual(our_3, l2_));
  }
}

TEST_F(ListTest, Merge) {
  std::list<int> stl_1 = {5, 9, 1, 3, 3};
  std::list<int> stl_2 = {8, 7, 2, 3, 4, 4};
  stl_1.merge(stl_2);
  list<int> our_1 = {5, 9, 1, 3, 3};
  list<int> our_2 = {8, 7, 2, 3, 4, 4};
  our_1.merge(our_2);
  EXPECT_TRUE(IsEqual(our_1, stl_1));
  EXPECT_TRUE(IsEqual(our_2, stl_2));
  stl_1.sort();
  stl_2.sort();
  stl_1.merge(stl_2);
  our_1.sort();
  our_2.sort();
  our_1.merge(our_2);
  EXPECT_TRUE(IsEqual(our_1, stl_1));
  EXPECT_TRUE(IsEqual(our_2, stl_2));
  list<int> our_3{1, 2, 3};
  our_3.merge(our_3);
  EXPECT_TRUE(IsEqual(our_3, l3_));
  list<int> our_4;
  our_4.merge(our_4);
  EXPECT_TRUE(IsEqual(our_4, l0_));
  std::list<int> stl_5 = {8, 7, 2, 3, 4, 4};
  std::list<int> stl_6 = {5, 9, 1, 3, 3};
  stl_5.merge(stl_6);
  list<int> our_5 = {8, 7, 2, 3, 4, 4};
  list<int> our_6 = {5, 9, 1, 3, 3};
  our_5.merge(our_6);
  EXPECT_TRUE(IsEqual(our_5, stl_5));
  EXPECT_TRUE(IsEqual(our_6, stl_6));
}

TEST_F(ListTest, Splice) {
  EXPECT_ANY_THROW(l0_.splice(l0_.begin(), l0_));
  EXPECT_ANY_THROW(l1_.splice(l1_.begin(), l1_));
  list<int> our_0;
  list<int> our_1{1};
  our_1.splice(our_1.begin(), our_0);
  EXPECT_TRUE(IsEqual(our_1, l1_));
  list<int> our_2{2};
  our_1.splice(our_1.end(), our_2);
  EXPECT_TRUE(IsEqual(our_1, l2_));
  EXPECT_TRUE(IsEqual(our_2, l0_));
  list<int> our_3{3};
  our_1.splice(our_1.end(), our_3);
  EXPECT_TRUE(IsEqual(our_1, l3_));
  EXPECT_TRUE(IsEqual(our_3, l0_));
  our_2.splice(our_2.begin(), our_1);
  EXPECT_TRUE(IsEqual(our_2, l3_));
  EXPECT_TRUE(IsEqual(our_1, l0_));
}

TEST_F(ListTest, Reverse) {
  list<int> our_0;
  our_0.reverse();
  EXPECT_TRUE(IsEqual(our_0, l0_));
  list<int> our_1{1};
  our_1.reverse();
  EXPECT_TRUE(IsEqual(our_1, l1_));
  list<int> our_2{2, 1};
  our_2.reverse();
  EXPECT_TRUE(IsEqual(our_2, l2_));
  list<int> our_3{3, 2, 1};
  our_3.reverse();
  EXPECT_TRUE(IsEqual(our_3, l3_));
}

TEST_F(ListTest, Unique) {
  list<int> our_0{};
  our_0.unique();
  EXPECT_TRUE(IsEqual(our_0, l0_));
  list<int> our_1{1};
  our_1.unique();
  EXPECT_TRUE(IsEqual(our_1, l1_));
  list<int> our_11{1, 1};
  our_11.unique();
  EXPECT_TRUE(IsEqual(our_11, l1_));
  list<int> our_111{1, 1, 1};
  our_111.unique();
  EXPECT_TRUE(IsEqual(our_111, l1_));
  list<int> our_2{1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3};
  our_2.unique();
  EXPECT_TRUE(IsEqual(our_2, l3_));
}

TEST_F(ListTest, Sort) {
  list<int> our_0;
  our_0.sort();
  EXPECT_TRUE(IsEqual(our_0, l0_));
  list<int> our_1{1};
  our_1.sort();
  EXPECT_TRUE(IsEqual(our_1, l1_));
  list<int> our_2{2, 1};
  our_2.sort();
  EXPECT_TRUE(IsEqual(our_2, l2_));
  our_2.sort();
  EXPECT_TRUE(IsEqual(our_2, l2_));
  list<int> our_3{3, 1, 2};
  our_3.sort();
  EXPECT_TRUE(IsEqual(our_3, l3_));
}

TEST_F(ListTest, IteratorPref) {
  list<int>::iterator iter = l2_.end();
  EXPECT_EQ(*iter, 0);
  ++iter;
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 0);
  list<int>::iterator iter_check = ++iter;
  EXPECT_EQ(*iter, 1);
  EXPECT_EQ(*iter_check, 1);
  --iter;
  EXPECT_EQ(*iter, 0);
  --iter;
  EXPECT_EQ(*iter, 2);
  --iter;
  EXPECT_EQ(*iter, 1);
  --iter;
  EXPECT_EQ(*iter, 0);
  --iter;
  EXPECT_EQ(*iter, 2);
}

TEST_F(ListTest, IteratorPost) {
  list<int>::iterator iter = l2_.end();
  EXPECT_EQ(*iter, 0);
  iter++;
  EXPECT_EQ(*iter, 1);
  iter++;
  EXPECT_EQ(*iter, 2);
  iter++;
  EXPECT_EQ(*iter, 0);
  list<int>::iterator iter_check = iter++;
  EXPECT_EQ(*iter, 1);
  EXPECT_EQ(*iter_check, 0);
  iter--;
  EXPECT_EQ(*iter, 0);
  iter--;
  EXPECT_EQ(*iter, 2);
  iter--;
  EXPECT_EQ(*iter, 1);
  iter--;
  EXPECT_EQ(*iter, 0);
  iter--;
  EXPECT_EQ(*iter, 2);
}

TEST_F(ListTest, IteratorPlusMinus) {
  list<int>::iterator iter = l2_.end();
  iter + 1;
  EXPECT_EQ(*iter, 1);
  iter - 1;
  EXPECT_EQ(*iter, 0);
  iter + 2;
  EXPECT_EQ(*iter, 2);
  iter - 2;
  EXPECT_EQ(*iter, 0);
  iter + 3;
  EXPECT_EQ(*iter, 0);
  iter - 3;
  EXPECT_EQ(*iter, 0);
}

TEST_F(ListTest, IteratorEqNonEq) {
  list<int>::iterator iter_1 = l2_.end();
  list<int>::iterator iter_2 = l2_.end();
  EXPECT_TRUE(iter_1 == iter_2);
  EXPECT_FALSE(iter_1 != iter_2);
  iter_2 = l3_.end();
  EXPECT_TRUE(iter_1 != iter_2);
  EXPECT_FALSE(iter_1 == iter_2);
}

TEST_F(ListTest, IterarorNull) {
  list<int>::iterator iter;
  EXPECT_ANY_THROW(*iter);
  EXPECT_ANY_THROW(++iter);
  EXPECT_ANY_THROW(iter++);
  EXPECT_ANY_THROW(--iter);
  EXPECT_ANY_THROW(iter--);
  EXPECT_ANY_THROW(iter + 1);
  EXPECT_ANY_THROW(iter - 1);
}

TEST_F(ListTest, InsertMany) {
  l0_.insert_many(l0_.begin(), 1);
  EXPECT_TRUE(IsEqual(l0_, l1_));
  l0_.insert_many(l0_.end(), 2, 3);
  EXPECT_TRUE(IsEqual(l0_, l3_));
  l0_.insert_many(l0_.end() - 1, 4);
  EXPECT_EQ(*(l0_.end() - 2), 4);
  EXPECT_EQ(l0_.size(), 4);
}

TEST_F(ListTest, InsertManyBack) {
  l0_.insert_many_back(1);
  EXPECT_TRUE(IsEqual(l0_, l1_));
  l0_.insert_many_back(2, 3);
  EXPECT_TRUE(IsEqual(l0_, l3_));
}

TEST_F(ListTest, InsertManyFront) {
  l0_.insert_many_front(1, 2, 3);
  EXPECT_TRUE(IsEqual(l0_, l3_));
  l0_.insert_many_front(4);
  EXPECT_EQ(*(l0_.end() + 1), 4);
  EXPECT_EQ(l0_.size(), 4);
}

template <typename value_type>
bool IsEqual(list<value_type> &our, std::list<value_type> &compared) {
  if (compared.size() != our.size()) {
    return false;
  }
  auto our_iter = our.begin();
  auto compared_iter = compared.begin();
  for (size_t i = 0; i < compared.size(); ++i, ++our_iter, ++compared_iter) {
    if (*our_iter != *compared_iter) {
      return false;
    }
  }
  return true;
}

template <typename value_type>
bool IsEqual(list<value_type> &our, list<value_type> &compared) {
  if (compared.size() != our.size()) {
    return false;
  }
  auto our_iter = our.begin();
  auto compared_iter = compared.begin();
  for (size_t i = 0; i < compared.size(); ++i, ++our_iter, ++compared_iter) {
    if (*our_iter != *compared_iter) {
      return false;
    }
  }
  return true;
}

}  // namespace s21
