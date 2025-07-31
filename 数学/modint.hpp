#include <cassert>
#include <iostream>

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
  mint operator/(mint rhs) { return x * rhs.inv(); }

  mint& operator+=(mint rhs) { return *this = *this + rhs; }
  mint& operator-=(mint rhs) { return *this = *this - rhs; }
  mint& operator*=(mint rhs) { return *this = *this * rhs; }
  mint& operator/=(mint rhs) { return *this = *this / rhs; }

  mint inv() const {
    if (x == 0) {
      throw logic_error("");
    }
    ll a = mod, b = x, u = 0, v = 1;
    while (b) {
      ll t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    assert(a == 1);
    return mint(u);
  }

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

  auto operator<=>(const mint&) const = default;
};


mint operator"" _m(unsigned long long x) { return x; }

istream& operator>>(istream& is, mint& x) {
  ll a;
  is >> a;
  x = a;
  return is;
}

template<>
struct std::hash<mint> {
  size_t operator()(mint x) { return hash<ll>()(x.x); }
};