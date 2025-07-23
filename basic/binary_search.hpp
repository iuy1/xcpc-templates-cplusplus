#include <numeric>
using std::midpoint;

// find first x in [l,r) thar f(x) is true
int binary_search(int l, int r, auto f) {
  if (l == r) {
    return l;
  }
  int mid = midpoint(l, r);
  if (f(mid)) {
    return binary_search(l, mid, f);
  } else {
    return binary_search(mid + 1, r, f);
  }
}
