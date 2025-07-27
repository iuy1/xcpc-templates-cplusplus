#include "mersenne_mod.hpp"

#include "gtest/gtest.h"

#include <random>
#include <ranges>

using namespace std;

TEST(Mersenne, Rand) {
  mt19937 gen(0);
  for (int i : views::iota(0, 1000)) {
    ulll x = ulll(gen()) << 64 | gen();
    EXPECT_EQ(remainder(x), x % mod);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}