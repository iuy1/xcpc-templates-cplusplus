#include <algorithm>
#include <bit>
#include <cassert>
#include <complex>
#include <vector>
#include <span>
#include <ranges>

using namespace std;

using ll = decltype(0LL);
const ll mod = 998'244'353;

struct mint {
  ll x;
  mint(ll _x = 0) : x(_x % mod) { x += (x < 0) * mod; }
  operator ll() { return x; }

  mint operator-() { return -x; }
  mint operator+(mint rhs) { return x + rhs.x; }
  mint operator-(mint rhs) { return x - rhs.x; }
  mint operator*(mint rhs) { return x * rhs.x; }
  mint& operator*=(mint rhs) { return *this = *this * rhs; }

  mint pow(ll n) const {
    if (n < 0) {
      throw invalid_argument("");
    }
    mint x = *this;
    mint res = mint(1);
    while (n) {
      if (n & 1)
        res *= x;
      x *= x;
      n >>= 1;
    }
    return res;
  }
};

void ntt(span<mint> a, span<int> rev) {
  assert(a.size() == rev.size());
  assert(has_single_bit(a.size()));
  auto n = a.size();
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) {
      swap(a[i], a[rev[i]]);
    }
  }
  for (int h = 2; h <= n; h <<= 1) {
    mint wn = mint(3).pow((mod - 1) / h);
    for (int j = 0; j < n; j += h) {
      mint w = 1;
      for (int k = j; k < j + h / 2; k++) {
        mint u = a[k], v = a[k + h / 2] * w;
        a[k] = u + v;
        a[k + h / 2] = u - v;
        w *= wn;
      }
    }
  }
}

void intt(span<mint> a, span<int> rev) {
  ntt(a, rev);
  auto n = a.size();
  reverse(a.begin() + 1, a.end());
  auto inv_n = mint(n).pow(mod - 2);
  for (int i = 0; i < n; i++) {
    a[i] *= inv_n;
  }
}

auto bit_rev(size_t n) {
  assert(has_single_bit(n));
  int len = countr_zero(n);
  vector<int> rev(n);
  for (int i = 0; i < n; i++) {
    rev[i] = rev[i >> 1] >> 1 | (i & 1) << (len - 1);
  }
  return rev;
}

vector<ll> ntt_mul(vector<ll> a, vector<ll> b) {
  auto n = a.size() * 2;
  a.resize(n), b.resize(n);
  auto rev = bit_rev(n);
  auto& am = reinterpret_cast<vector<mint>&>(a);
  auto& bm = reinterpret_cast<vector<mint>&>(b);
  ntt(am, rev);
  ntt(bm, rev);
  for (auto&& [ai, bi] : views::zip(a, b)) {
    ai *= bi;
  }
  intt(am, rev);
  return a;
}