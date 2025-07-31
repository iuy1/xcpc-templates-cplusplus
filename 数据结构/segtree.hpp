#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <vector>
#include <span>
#include <optional>

using namespace std;
using ll = decltype(0LL);


// [1] 0..N-1
// [2] 0..N/2-1  [3] N/2..N-1
// ...
// [N] 0  [N+1] 1  ...  [N+n] n
struct segtree {
  struct node {
    ll sum;
    ll max;
    ll tag_add;
    optional<ll> tag_set; // tag_add should be 0 if tag_set exist
    // pair<ll,ll> max;
  };

  node unit{0, numeric_limits<ll>::min()};

  size_t n;
  size_t lg_N, N;
  vector<node> nodes;
  int offset = 0;
  auto size() { return n; }

  auto merge(node a, node b) {
    node r{};
    r.sum = a.sum + b.sum;
    r.max = max(a.max, b.max);
    return r;
  }

  auto maintain(size_t i, size_t len) {
    nodes[i] = merge(nodes[i << 1], nodes[i << 1 | 1]);
  }

  void propagate(size_t i, int len) {
    node& p = nodes[i];
    node* sons[]{&nodes[i << 1], &nodes[i << 1 | 1]};
    auto half_len = len / 2;
    if (p.tag_set) {
      assert(p.tag_add == 0);
      for (int s : {0, 1}) {
        sons[s]->sum = *p.tag_set * half_len;
        sons[s]->max = *p.tag_set;
        sons[s]->tag_set = p.tag_set;
      }
      p.tag_set = nullopt;
    } else if (p.tag_add) {
      for (int s : {0, 1}) {
        sons[s]->sum += p.tag_add * half_len;
        sons[s]->max += p.tag_add;
        sons[s]->tag_add += p.tag_add;
      }
      p.tag_add = 0;
    }
  }

  // index [1, n] -> [N+1, N+n]
  segtree(size_t n) : n(n),
                      lg_N(bit_width(n + 1)), N(1 << lg_N),
                      nodes(N << 1) {
    assert(n+2 <= N);
  }

  segtree(span<ll const> a) : segtree(a.size() - 1) {
    if (a.front() != 0) {
      throw invalid_argument("");
    }
    for (int i = 1; i <= n; i++) {
      node& p = nodes[N + i];
      p.sum = p.max = a[i];
    }
    for (int i = lg_N - 1; i >= 0; i--) {
      for (int j = 1 << i; j < 1 << (i + 1); j++) {
        maintain(j, N >> i);
      }
    }
  }

  auto access(size_t l, size_t r, auto modify) {
    l += offset, r += offset;
    if (l > r || l == 0 || r > n) {
      throw out_of_range("");
    }
    l += N - 1, r += N + 1;
    for (int i = lg_N; i > 0; i--) {
      propagate(l >> i, 1 << i);
    }
    for (int i = bit_width(l ^ r) - 1; i > 0; i--) {
      propagate(r >> i, 1 << i);
    }
    node ansl = unit, ansr = unit;
    int len = 1;
    while ((l ^ r) != 1) {
      if ((l & 1) == 0) {
        modify(nodes[l ^ 1], len);
        ansl = merge(ansl, nodes[l ^ 1]);
      }
      if ((r & 1) == 1) {
        modify(nodes[r ^ 1], len);
        ansr = merge(nodes[r ^ 1], ansr);
      }
      l >>= 1, r >>= 1, len <<= 1;
      maintain(l, len), maintain(r, len);
    }
    l >>= 1, len <<= 1;
    while (l != 0) {
      maintain(l, len);
      l >>= 1;
      len <<= 1;
    }
    assert(len == N << 1);
    if constexpr (requires { modify(); }) {
      return merge(ansl, ansr);
    }
  }

  void add(size_t l, size_t r, ll val) {
    access(l, r, [&](node& p, int len) {
      p.sum += len * val;
      p.max += val;
      p.tag_add += val;
    });
  }

  void add(size_t p, ll val) {
    add(p, p, val);
  }

  void set(size_t l, size_t r, ll val) {
    access(l, r, [&](node& p, int len) {
      p.sum = len * val;
      p.max = val;
      p.tag_add = 0;
      p.tag_set = val;
    });
  }

  void set(size_t p, ll val) {
    set(p, p, val);
  }

  ll sum(size_t l, size_t r) {
    return access(l, r, [](auto...) {
    }).sum;
  }

  ll val(size_t p) {
    return sum(p, p);
  }

  ll max_v(size_t l, size_t r) {
    return access(l, r, [](auto...) {
    }).max;
  }

  void print() {
    for (int i = 1; i <= n; i++) {
      cerr << sum(i, i) << " ";
    }
    cerr << endl;
  }
};