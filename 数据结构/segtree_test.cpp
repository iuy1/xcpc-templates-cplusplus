#include "segtree.hpp"

#include <gtest/gtest.h>

TEST(Segtree, Segtree) {
  segtree st(vector<ll>{0, 1, 2, 3, 4});
  st.offset = 2;
  // [-1, 2]
  st.add(0, 1, 2);
  // [1, 4, 5, 4]
  ASSERT_EQ(st.sum(-1, 1), 10);
  ASSERT_EQ(st.max_v(1, 2), 5);
  st.set(-1, 2, 4);
  ASSERT_EQ(st.sum(1, 1), 4);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
