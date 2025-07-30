#include <numeric>
#include <vector>

using namespace std;

struct dsu {
  size_t n;
  vector<int> fa, size;
  size_t cnt; // count of sets

  dsu(size_t n) : n(n), fa(n), size(n, 1), cnt(n) {
    iota(fa.begin(), fa.end(), 0);
  }

  int find(int x) {
    if (x >= n)
      throw out_of_range("");
    if (fa[x] == x) {
      return x;
    }
    return fa[x] = find(fa[x]);
  }

  bool same(int x, int y) { return find(x) == find(y); }

  // return true if x and y are
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    if (size[x] < size[y]) {
      swap(x, y);
    }
    fa[y] = x;
    size[x] += size[y];
    cnt--;
    return true;
  }
};