#include <gtest/gtest.h>

#include <queue>

#include "../queue.h"

namespace s21 {

class QueueTest : public testing::Test {
 protected:
  queue<int> l0_;
  queue<int> l1_{1};
  queue<int> l2_{1, 2};
  queue<int> l3_{1, 2, 3};
};

template <typename value_type>
bool IsEqual(queue<value_type> &our, queue<value_type> &compared);

TEST_F(QueueTest, DefaultConstructor) {
  std::queue<int> stq;
  EXPECT_EQ(stq.size(), l0_.size());
}

TEST_F(QueueTest, ListConstructor) {
  std::queue<int> stq;
  stq.push(1);
  EXPECT_EQ(l1_.front(), stq.front());
  EXPECT_EQ(l1_.back(), stq.back());
  stq.push(2);
  EXPECT_EQ(l2_.front(), stq.front());
  EXPECT_EQ(l2_.back(), stq.back());
  stq.push(3);
  EXPECT_EQ(l3_.front(), stq.front());
  EXPECT_EQ(l3_.back(), stq.back());
}

TEST_F(QueueTest, CopyConstructor) {
  queue<int> copy{l3_};
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.front(), 1);
  EXPECT_EQ(copy.back(), 3);
  EXPECT_EQ(l3_.size(), 3);
  EXPECT_EQ(l3_.front(), 1);
  EXPECT_EQ(l3_.back(), 3);
}

TEST_F(QueueTest, MoveConstructor) {
  queue<int> our{1, 2, 3};
  queue<int> copy{std::move(our)};
  EXPECT_TRUE(IsEqual(copy, l3_));
  EXPECT_TRUE(IsEqual(our, l0_));
}

TEST_F(QueueTest, Destructor) {
  l0_.~queue();
  l1_.~queue();
  l2_.~queue();
  l3_.~queue();
  EXPECT_EQ(l0_.size(), 0);
  EXPECT_EQ(l1_.size(), 0);
  EXPECT_EQ(l2_.size(), 0);
  EXPECT_EQ(l3_.size(), 0);
}

TEST_F(QueueTest, CopyOperator) {
  queue<int> our{1, 2, 3};
  l0_ = our;
  EXPECT_EQ(l0_.size(), 3);
  EXPECT_TRUE(IsEqual(our, l0_));
}

TEST_F(QueueTest, MoveOperator) {
  queue<int> our{1, 2, 3};
  l0_ = std::move(our);
  EXPECT_EQ(our.size(), 0);
  EXPECT_TRUE(IsEqual(l0_, l3_));
}

TEST_F(QueueTest, Swap) {
  l0_.swap(l3_);
  EXPECT_EQ(l0_.size(), 3);
  EXPECT_EQ(l3_.size(), 0);
}

TEST_F(QueueTest, InsertManyBack) {
  s21::queue<int> l0_;
  l0_.insert_many_back(1);
  l0_.insert_many_back(2, 3);
  EXPECT_TRUE(IsEqual(l0_, l3_));
}

template <typename value_type>
bool IsEqual(queue<value_type> &our, queue<value_type> &compared) {
  if (our.size() != compared.size()) {
    return false;
  }
  while (!our.empty()) {
    if (our.front() != our.front()) {
      return false;
    }
    our.pop();
    compared.pop();
  }
  return true;
}

}  // namespace s21
