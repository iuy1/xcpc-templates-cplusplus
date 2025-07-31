#include <algorithm>
#include <bit>
#include <cassert>
#include <complex>
#include <vector>
#include <span>
#include <ranges>

using namespace std;

using ll = decltype(0LL);
using cpd = complex<double>;

const double pi = acos(-1);

namespace fft {
void fft(span<cpd> a, span<int> rev) {
  assert(a.size() == rev.size());
  assert(has_single_bit(a.size()));
  auto n = a.size();
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) {
      swap(a[i], a[rev[i]]);
    }
  }
  for (int h = 2; h <= n; h <<= 1) {
    cpd wn = polar(1.0, 2 * pi / h);
    for (int j = 0; j < n; j += h) {
      cpd w = 1;
      for (int k = j; k < j + h / 2; k++) {
        cpd u = a[k], v = a[k + h / 2] * w;
        a[k] = u + v;
        a[k + h / 2] = u - v;
        w *= wn;
      }
    }
  }
}

void ifft(span<cpd> a, span<int> rev) {
  fft(a, rev);
  auto n = a.size();
  reverse(a.begin() + 1, a.end());
  for (int i = 0; i < n; i++) {
    a[i] /= n;
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

vector<ll> fft_mul(vector<ll> a, vector<ll> b) {
  auto n = a.size() * 2;
  vector<cpd> aa(n);
  ranges::copy(a, aa.begin());
  vector<cpd> bb(n);
  ranges::copy(b, bb.begin());
  auto rev = bit_rev(n);
  fft(aa, rev);
  fft(bb, rev);
  for (auto&& [ai, bi] : views::zip(aa, bb)) {
    ai *= bi;
  }
  ifft(aa, rev);
  return aa
         | views::transform([](cpd x) -> ll { return round(x.real()); })
         | ranges::to<vector>();
}
}