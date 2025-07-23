#include "binary_search.hpp"

#include <gtest/gtest.h>

#include <vector>

using namespace std;


TEST(BinarySearch, EmptyRange) {
  auto f = [](int x) {
    throw std::runtime_error("");
    return false;
  };
  EXPECT_EQ(binary_search(0, 0, f), 0);
  EXPECT_EQ(binary_search(1, 1, f), 1);
  EXPECT_EQ(binary_search(-1, -1, f), -1);
}

TEST(BinarySearch, Normal) {
  auto gt = [](int a) {
    return [a](int x) {
      return x >= a;
    };
  };

  EXPECT_EQ(binary_search(0, 5, gt(-1)), 0);
  EXPECT_EQ(binary_search(0, 5, gt(0)), 0);
  EXPECT_EQ(binary_search(0, 5, gt(1)), 1);
  EXPECT_EQ(binary_search(0, 5, gt(2)), 2);
  EXPECT_EQ(binary_search(0, 5, gt(3)), 3);
  EXPECT_EQ(binary_search(0, 5, gt(4)), 4);
  EXPECT_EQ(binary_search(0, 5, gt(5)), 5);
  EXPECT_EQ(binary_search(0, 5, gt(6)), 5);
}

TEST(BinarySearch, Negtive) {
  EXPECT_EQ(midpoint(-2, -1), -2);
  EXPECT_EQ(midpoint(-1, -2), -1);
  EXPECT_EQ((-2 + -1) / 2, -1);

  auto gt = [](int a) {
    return [a](int x) {
      return x >= a;
    };
  };

  EXPECT_EQ(binary_search(-2, -1, gt(-1)), -1);
  EXPECT_EQ(binary_search(-3, -1, gt(-3)), -3);
}

TEST(BinarySearch, CallsRequired) {
  vector<int> visit;
  auto gt = [&visit](int a) {
    return [&visit, a](int x) {
      visit.push_back(x);
      return x >= a;
    };
  }; {
    visit.clear();
    binary_search(0, 2, gt(1));
    vector exp{1, 0};
    EXPECT_EQ(visit, exp);
  } {
    visit.clear();
    binary_search(0, 2, gt(2));
    vector exp{1};
    EXPECT_EQ(visit, exp);
  } {
    visit.clear();
    binary_search(0, 7, gt(3));
    vector exp{3, 1, 2};
    EXPECT_EQ(visit, exp);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}