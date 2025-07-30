#include "dsu.hpp"

#include <gtest/gtest.h>

TEST(Dsu, Dsu) {
  dsu d(5);
  d.unite(0, 1);
  d.unite(1, 2);
  // [0, 1, 2], [3], [4]
  EXPECT_TRUE(d.same(0, 2));
  EXPECT_FALSE(d.same(3, 4));
  EXPECT_THROW(d.find(5), out_of_range);
  EXPECT_EQ(d.cnt, 3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
