#include "fenwick.hpp"

#include <gtest/gtest.h>

TEST(Fenwick, Fenwick) {
  fenwick fen(10);
  fen.add(1, 1);
  fen.add(3, 2);
  // [1, 0, 2, ...]
  EXPECT_THROW(fen.add(0, 1), std::out_of_range);
  EXPECT_THROW(fen.add(11, 1), std::out_of_range);
  EXPECT_EQ(fen.query(5), 3);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
