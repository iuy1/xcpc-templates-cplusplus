#include "karatsuba.hpp"
#include "fft.hpp"
#include "ntt.hpp"

#include <gtest/gtest.h>


TEST(Mul, Kara) {
  vector<ll> a{1, 2, 3, 4};
  vector<ll> b{5, 6, 7, 8};
  auto ka = kara_mul<1>(a, b);
  auto fft = fft::fft_mul(a, b);
  auto ntt = ntt_mul(a, b);
  ASSERT_EQ(ka, fft);
  ASSERT_EQ(fft, ntt);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}