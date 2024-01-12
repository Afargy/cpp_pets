#include <gtest/gtest.h>

#include <stack>

#include "../stack.h"

namespace s21 {

class StackTest : public testing::Test {
 protected:
  stack<int> l0_;
  stack<int> l1_{1};
  stack<int> l2_{1, 2};
  stack<int> l3_{1, 2, 3};
};

TEST_F(StackTest, DefaultConstructor) {
  std::stack<int> sts;
  EXPECT_EQ(sts.size(), l0_.size());
}

TEST_F(StackTest, InitListConstructor) {
  EXPECT_EQ(l1_.top(), 1);
  EXPECT_EQ(l2_.top(), 2);
  EXPECT_EQ(l3_.top(), 3);
}

TEST_F(StackTest, CopyConstructor) {
  stack<int> our_0{l0_};
  EXPECT_TRUE(our_0.empty());
  stack<int> our_1{l1_};
  EXPECT_FALSE(l1_.empty());
  EXPECT_EQ(our_1.top(), 1);
  stack<int> our_2{l2_};
  EXPECT_FALSE(l2_.empty());
  EXPECT_EQ(our_2.top(), 2);
  stack<int> our_3{l3_};
  EXPECT_FALSE(l3_.empty());
  EXPECT_EQ(our_3.top(), 3);
}

TEST_F(StackTest, MoveConstructor) {
  stack<int> our_0{std::move(l0_)};
  EXPECT_TRUE(our_0.empty());
  stack<int> our_1{std::move(l1_)};
  EXPECT_TRUE(l1_.empty());
  EXPECT_EQ(our_1.top(), 1);
  stack<int> our_2{std::move(l2_)};
  EXPECT_TRUE(l2_.empty());
  EXPECT_EQ(our_2.top(), 2);
  stack<int> our_3{std::move(l3_)};
  EXPECT_TRUE(l3_.empty());
  EXPECT_EQ(our_3.top(), 3);
}

TEST_F(StackTest, Destructor) {
  l0_.~stack();
  l1_.~stack();
  l2_.~stack();
  l3_.~stack();
  EXPECT_EQ(l0_.size(), 0);
  EXPECT_EQ(l1_.size(), 0);
  EXPECT_EQ(l2_.size(), 0);
  EXPECT_EQ(l3_.size(), 0);
}

TEST_F(StackTest, CopyOperator) {
  stack<int> our{1, 2, 3};
  l0_ = our;
  EXPECT_EQ(l0_.size(), 3);
  EXPECT_EQ(our.size(), 3);
  EXPECT_EQ(our.top(), 3);
  EXPECT_EQ(l0_.top(), 3);
}

TEST_F(StackTest, MoveOperator) {
  stack<int> our{1, 2, 3};
  l0_ = std::move(our);
  EXPECT_EQ(our.size(), 0);
  EXPECT_TRUE(our.empty());
}

TEST_F(StackTest, Empty) {
  EXPECT_TRUE(l0_.empty());
  EXPECT_FALSE(l1_.empty());
  EXPECT_FALSE(l2_.empty());
  EXPECT_FALSE(l3_.empty());
}

TEST_F(StackTest, Size) {
  EXPECT_EQ(l0_.size(), 0);
  EXPECT_EQ(l1_.size(), 1);
  EXPECT_EQ(l2_.size(), 2);
  EXPECT_EQ(l3_.size(), 3);
}

TEST_F(StackTest, Push) {
  l0_.push(100);
  EXPECT_EQ(l0_.size(), 1);
  EXPECT_EQ(l0_.top(), 100);
}

TEST_F(StackTest, Pop) {
  EXPECT_ANY_THROW(l0_.pop());
  l1_.pop();
  EXPECT_TRUE(l1_.empty());
  l2_.pop();
  EXPECT_EQ(l2_.size(), 1);
  EXPECT_EQ(l2_.top(), 1);
}

TEST_F(StackTest, Swap) {
  l0_.swap(l3_);
  l1_.swap(l2_);
  EXPECT_EQ(l0_.size(), 3);
  EXPECT_EQ(l0_.top(), 3);
  EXPECT_EQ(l3_.size(), 0);
  EXPECT_ANY_THROW(l3_.top());
  EXPECT_EQ(l1_.size(), 2);
  EXPECT_EQ(l1_.top(), 2);
  EXPECT_EQ(l2_.size(), 1);
  EXPECT_EQ(l2_.top(), 1);
}

TEST_F(StackTest, InserManyFront) {
  l0_.insert_many_front(3);
  EXPECT_EQ(l0_.top(), 3);
  EXPECT_EQ(l0_.size(), 1);
  l0_.insert_many_front(1, 2);
  EXPECT_EQ(l0_.top(), 3);
  EXPECT_EQ(l0_.size(), 3);
}

}  // namespace s21
