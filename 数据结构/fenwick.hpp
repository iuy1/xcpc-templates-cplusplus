#include <vector>

using std::vector;

using ll = decltype(0LL);

struct fenwick {
  size_t n;
  vector<ll> a; // 1 index

  fenwick(size_t n) : n(n), a(n + 1) {
  }

  void add(size_t i, ll x) {
    if (i == 0 || i > n) {
      throw std::out_of_range("");
    }
    while (i <= n) {
      a[i] += x;
      i += i & -i;
    }
  }

  ll query(size_t i) {
    if (i > n) {
      throw std::out_of_range("");
    }
    ll res = 0;
    while (i > 0) {
      res += a[i];
      i -= i & -i;
    }
    return res;
  }
};