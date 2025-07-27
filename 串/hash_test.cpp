#include "hash.hpp"

#include "gtest/gtest.h"

#include <random>

using namespace std;

TEST(Hash, Hash) {
  string s(99, 'a');
  s = s + 'b' + s + 'c';
  ASSERT_EQ(s.size(), 200) << s;
  string_hash h(s);
  EXPECT_EQ(h.get(0, 98), h.get(100, 198));
  EXPECT_NE(h.get(0, 99), h.get(100, 199));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}