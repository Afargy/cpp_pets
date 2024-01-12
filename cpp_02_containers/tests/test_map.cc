#include <gtest/gtest.h>

#include <map>

#include "../map.h"

namespace s21 {

class MapTest : public testing::Test {
 protected:
  map<int, int> l0_;
  map<int, int> l1_{{1, 10}};
  map<int, int> l2_{{1, 10}, {2, 20}};
  map<int, int> l3_{{1, 10}, {2, 20}, {3, 30}};
  map<int, std::string> m3_{{1, "one"}, {2, "two"}, {3, "three"}};
  map<int, int>::iterator it_{nullptr};
};

TEST_F(MapTest, Constructors) {
  EXPECT_EQ(l0_.size(), 0);
  EXPECT_EQ(l3_.size(), 3);
  l0_ = std::move(l3_);
  EXPECT_EQ(l0_.size(), 3);
  EXPECT_EQ(l3_.size(), 0);
  s21::map<int, int> our_1{l2_};
  EXPECT_EQ(our_1.size(), 2);
  EXPECT_EQ(l2_.size(), 2);
  s21::map<int, int> our_2{std::move(l3_)};
  EXPECT_EQ(our_2.size(), 0);
  EXPECT_EQ(l3_.size(), 0);
  s21::map<int, int> our_3{{1, 10}, {2, 20}};
  EXPECT_EQ(l2_[1], our_3[1]);
  EXPECT_EQ(l2_[2], our_3[2]);
  EXPECT_EQ(m3_.size(), 3);
  EXPECT_FALSE(m3_.empty());
  EXPECT_EQ(m3_.at(1), "one");
  EXPECT_EQ(m3_.at(2), "two");
  EXPECT_EQ(m3_.at(3), "three");
  s21::map<int, std::string> copy_m(m3_);
  EXPECT_EQ(copy_m.size(), 3);
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}

TEST_F(MapTest, Clear) {
  l3_.clear();
  EXPECT_EQ(l3_.size(), 0);
  EXPECT_EQ(l3_.empty(), 1);
  l3_.clear();
  l2_.~map();
  EXPECT_EQ(l2_.size(), 0);
  EXPECT_EQ(l2_.empty(), 1);
}

TEST_F(MapTest, SizeEmpty) {
  EXPECT_EQ(l0_.size(), 0);
  EXPECT_EQ(l0_.empty(), 1);
  EXPECT_EQ(l3_.size(), 3);
  EXPECT_EQ(l3_.empty(), 0);
  EXPECT_FALSE(m3_.empty());
  EXPECT_EQ(m3_.size(), 3);
}

TEST_F(MapTest, Insert) {
  l0_.insert({1, 10});
  EXPECT_EQ(l0_.size(), 1);
  EXPECT_EQ(l0_[1], 10);
  l0_.insert(2, 20);
  EXPECT_EQ(l0_.size(), 2);
  EXPECT_EQ(l0_[1], 10);
  EXPECT_EQ(l0_[2], 20);
  s21::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(2, "two");
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
  s21::map<int, std::string> map_1;
  map_1.insert(1, "one");
  EXPECT_EQ(map_1.size(), 1);
  EXPECT_EQ(map_1.contains(1), true);
  EXPECT_EQ(map_1[1], "one");
  map_1.insert(2, "two");
  EXPECT_EQ(map_1.size(), 2);
  EXPECT_EQ(map_1.contains(1), true);
  EXPECT_EQ(map_1[1], "one");
  EXPECT_EQ(map_1.contains(2), true);
  EXPECT_EQ(map_1[2], "two");
  s21::map<int, std::string> map_2;
  map_2.insert(std::make_pair(1, "one"));
  EXPECT_EQ(map_2.size(), 1);
  EXPECT_EQ(map_2.contains(1), true);
  EXPECT_EQ(map_2[1], "one");
  map_2.insert(std::make_pair(2, "two"));
  EXPECT_EQ(map_2.size(), 2);
  EXPECT_EQ(map_2.contains(1), true);
  EXPECT_EQ(map_2[1], "one");
  EXPECT_EQ(map_2.contains(2), true);
  EXPECT_EQ(map_2[2], "two");
}

TEST_F(MapTest, InsertOrAssign) {
  s21::map<int, std::string> map;
  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(it1->first, 1);
  EXPECT_EQ(it1->second, "one");
  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, "ONE");
  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}

TEST_F(MapTest, AtAndOperatorBrackets) {
  EXPECT_EQ(m3_.at(1), "one");
  EXPECT_EQ(m3_[2], "two");
  EXPECT_ANY_THROW(m3_.at(4));
  m3_[4] = "four";
  EXPECT_EQ(m3_[4], "four");
  m3_[2] = "TWO";
  EXPECT_EQ(m3_[2], "TWO");
}

TEST_F(MapTest, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> map1;
  EXPECT_GT(map.max_size(), map1.max_size());
}

TEST_F(MapTest, Erase) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({4, "five"});
  auto it = map.begin();
  map.erase(it);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
  it = map.begin();
  map.erase(it);
  EXPECT_EQ(map.size(), 2);
  EXPECT_FALSE(map.contains(2));
  it = map.begin();
  map.erase(it);
  EXPECT_EQ(map.size(), 1);
  EXPECT_FALSE(map.contains(3));
  it = map.begin();
  map.erase(it);
  EXPECT_EQ(map.size(), 0);
  EXPECT_FALSE(map.contains(4));
  it = map.begin();
  EXPECT_NO_THROW(map.erase(it));
  it = m3_.end();
  m3_.erase(it);
  EXPECT_EQ(m3_.size(), 2);
  EXPECT_FALSE(m3_.contains(3));
  it = m3_.end();
  m3_.erase(it);
  EXPECT_EQ(m3_.size(), 1);
  EXPECT_FALSE(m3_.contains(2));
  it = m3_.end();
  m3_.erase(it);
  EXPECT_EQ(m3_.size(), 0);
  EXPECT_FALSE(m3_.contains(0));
  it = m3_.end();
  EXPECT_NO_THROW(m3_.erase(it));
}

TEST_F(MapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});
  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST_F(MapTest, Merge) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});
  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST_F(MapTest, Contains) {
  s21::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST_F(MapTest, Iterators) {
  it_ = l3_.end();
  EXPECT_EQ(it_->second, 30);
  it_ = l3_.begin();
  EXPECT_EQ(it_->second, 10);
  l3_.insert({4, 40});
  l3_.insert({5, 50});
  l3_.insert({6, 60});
  l3_.insert({7, 70});
  l3_.insert({8, 80});
  l3_.insert({9, 90});
  l3_.insert({10, 100});
  it_ = l3_.begin();
  for (size_t i = 1; i < 15; ++i) {
    if (i < 10) {
      EXPECT_EQ(it_->first, i);
    } else {
      EXPECT_EQ(it_->first, 10);
    }
    ++it_;
  }
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(it_->first, 10 - i);
    --it_;
  }
  EXPECT_NO_THROW(--it_);
  for (size_t i = 1; i < 15; ++i) {
    if (i < 10) {
      EXPECT_EQ(it_->first, i);
    } else {
      EXPECT_EQ(it_->first, 10);
    }
    it_++;
  }
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(it_->first, 10 - i);
    it_--;
  }
  it_ = it_ + 2;
  EXPECT_EQ(it_->first, 3);
  it_ = it_ - 2;
  EXPECT_EQ(it_->first, 1);
  EXPECT_NO_THROW(it_--);
  EXPECT_TRUE(it_ == l3_.begin());
  EXPECT_FALSE(it_ == l2_.begin());
  ++it_;
  EXPECT_FALSE(it_ == l3_.begin());
  it_ = nullptr;
  EXPECT_ANY_THROW(++it_);
}

TEST_F(MapTest, At) {
  EXPECT_EQ(l3_.at(3), 30);
  l3_.at(3) = 123;
  EXPECT_EQ(l3_.at(3), 123);
  EXPECT_ANY_THROW(l3_.at(30));
  EXPECT_EQ(l3_[3], 123);
  l3_[3] = 30;
  EXPECT_EQ(l3_[3], 30);
  EXPECT_NO_THROW(l3_[30]);
  it_ = l3_.end();
  EXPECT_EQ(it_->second, 30);
  it_->second = 300;
  EXPECT_EQ(it_->second, 300);
  EXPECT_EQ(it_->first, 3);
  map<int, int>::const_iterator cit{l3_.end()};
  EXPECT_EQ(cit->second, 300);
}

TEST_F(MapTest, Additional) {
  l0_.insert(1, 1);
  l0_.insert(2, 2);
  l0_.insert(4, 4);
  l0_.insert(5, 5);
  l0_.insert(6, 6);
  l0_.insert(3, 3);
  l0_.insert(7, 7);
  l0_.insert(13, 13);
  l0_.insert(14, 14);
  l0_.insert(15, 15);
  l0_.insert(8, 8);
  l0_.insert(9, 9);
  l0_.insert(10, 10);
  l0_.insert(11, 11);
  l0_.insert(12, 12);
  l0_.insert(16, 16);
  l0_.insert(17, 17);
  l0_.insert(18, 18);
  EXPECT_EQ(l0_.size(), 18);
  it_ = l0_.begin();
  while (it_->first != 5) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 16) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 14) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 9) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 8) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 3) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 10) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 13) {
    ++it_;
  }
  l0_.erase(it_);
  it_ = l0_.begin();
  while (it_->first != 17) {
    ++it_;
  }
  l0_.erase(it_);

  map<int, int> our;
  our.insert(1, 1);
  our.insert(2, 2);
  our.insert(13, 13);
  our.insert(3, 3);
  our.insert(5, 5);
  our.insert(8, 8);
  our.insert(7, 7);
  our.insert(4, 4);

  our.clear();
  our.insert(4, 4);
  our.erase(our.begin());
}

}  // namespace s21
