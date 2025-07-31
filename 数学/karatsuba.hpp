#include <bit>
#include <cassert>
#include <valarray>
#include <vector>

using namespace std;

using ll = decltype(0LL);
using vll = valarray<ll>;


template <int N = 32>
vll karatsuba(vll a, vll b) {
  assert(a.size() == b.size());
  auto len = a.size();
  assert(has_single_bit(len));
  vll res(len * 2);
  if (len <= N) {
    for (int i = 0; i < len; i++) {
      res[slice(i, len, 1)] += a * b[i];
    }
    return res;
  }
  auto half = len / 2;
  vll la = a[slice(0, half, 1)], ha = a[slice(half, half, 1)];
  vll lb = b[slice(0, half, 1)], hb = b[slice(half, half, 1)];
  vll z0 = karatsuba<N>(la, lb);
  vll z1 = karatsuba<N>(la + ha, lb + hb);
  vll z2 = karatsuba<N>(ha, hb);
  res[slice(0, len, 1)] += z0;
  res[slice(half, len, 1)] += z1 - z0 - z2;
  res[slice(len, len, 1)] += z2;
  return res;
}

template <int N = 32>
vector<ll> kara_mul(vector<ll> a, vector<ll> b) {
  vll r = karatsuba<N>(vll(a.data(), a.size()), vll(b.data(), b.size()));
  return vector(begin(r), end(r));
}
