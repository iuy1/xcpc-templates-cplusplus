#include <array>
#include <cassert>
#include <cstddef>

using namespace std;

array<byte, 128 * 1024 * 1024> buffer;
size_t offset;

template <class T>
struct alloc {
  using value_type = T;

  static void reset() {
    offset = 0;
  }

  static T* allocate(size_t n) {
    T* r = reinterpret_cast<T*>(buffer.data() + offset);
    n *= sizeof(T);
    offset += n;
    assert(offset < buffer.size());
    return r;
  }

  static void deallocate(T* p, size_t n) {
  }
};