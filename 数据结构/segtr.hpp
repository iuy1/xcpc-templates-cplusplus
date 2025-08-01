#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <optional>
#include <span>
#include <vector>

using namespace std;
using ll = decltype(0LL);

// 0 index
struct segtr {
  struct node {
    ll sum;
    ll max;
    ll tag_add;
    optional<ll> tag_set;  // tag_add should be 0 if tag_set exist
    // pair<ll,ll> max;
  };

  node unit{0, numeric_limits<ll>::min()};

  size_t n;
  size_t lg_N, N;
  vector<node> nodes;
  // int offset = 0;
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

  segtr(size_t n) : n(n), nodes(n * 4) {}

  segtr(span<ll const> a) : segtr(a.size()) {
    for (int i = 0; i < n; i++) {
      set(i, a[i]);
    }
  }

  // void modify(node&, len)
  auto access(size_t l, size_t r, auto modify) {
    auto rec = [&](this auto& rec, size_t p, size_t pl, size_t pr) {
      node& np = nodes[p];
      auto len = pr - pl + 1;
      if (l <= pl && pr <= r) {
        modify(np, len);
        return np;
      }
      if (r < pl || pr < l) {
        return unit;
      }
      propagate(p, len);
      auto mid = midpoint(pl, pr);
      auto ansl = rec(p * 2, pl, mid);
      auto ansr = rec(p * 2 + 1, mid + 1, pr);
      maintain(p, len);
      return merge(ansl, ansr);
    };
    return rec(1, 0, n - 1);
  }

  void add(size_t l, size_t r, ll val) {
    access(l, r, [&](node& p, int len) {
      p.sum += len * val;
      p.max += val;
      p.tag_add += val;
    });
  }

  void add(size_t p, ll val) { add(p, p, val); }

  void set(size_t l, size_t r, ll val) {
    access(l, r, [&](node& p, int len) {
      p.sum = len * val;
      p.max = val;
      p.tag_add = 0;
      p.tag_set = val;
    });
  }

  void set(size_t p, ll val) { set(p, p, val); }

  ll sum(size_t l, size_t r) {
    return access(l, r, [](auto...) {}).sum;
  }

  ll val(size_t p) { return sum(p, p); }

  ll max_v(size_t l, size_t r) {
    return access(l, r, [](auto...) {}).max;
  }

  void print() {
    for (int i = 0; i < n; i++) {
      cerr << sum(i, i) << " ";
    }
    cerr << endl;
  }
};