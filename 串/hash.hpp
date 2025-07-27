#include <vector>

using namespace std;

using ulll = __uint128_t;

const ulll mod = (ulll(1) << 61) - 1;
const unsigned base = 100;

__attribute__((always_inline)) ulll remainder(ulll x) {
  x = (x & mod) + (x >> 61);
  return (x & mod) + (x >> 61);
}

struct string_hash {
  vector<ulll> pow;
  vector<ulll> hash;

  template <class T>
    requires requires(T t) { t.begin(); }
  string_hash(T s) {
    pow.reserve(s.size() + 1), hash.reserve(s.size() + 1);
    pow.push_back(1), hash.push_back(0);
    for (unsigned x : s) {
      push_back(x);
    }
  }

  void push_back(unsigned x) {
    pow.push_back(remainder(pow.back() * base));
    hash.push_back(remainder(hash.back() * base + x));
  }

  // hash of sub string [l, r]
  auto get(int l, int r) const {
    return remainder(hash[r + 1] + mod - remainder(hash[l] * pow[r - l + 1]));
  }

  operator ulll() const { return hash.back(); }
};