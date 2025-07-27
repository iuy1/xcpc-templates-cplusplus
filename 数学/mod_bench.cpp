#include "mersenne_mod.hpp"

#include <benchmark/benchmark.h>

#include <random>

using namespace std;

void BM_empty(benchmark::State& state) {
  mt19937 gen(42);
  const int N = 1000;
  vector<int> v(N);
  for (int& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x);
    }
  }
}

BENCHMARK(BM_empty);


void BM_i32_const(benchmark::State& state) {
  mt19937 gen(42);
  constexpr int mod = 1000'000'007;
  const int N = 1000;
  vector<int> v(N);
  for (int& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i32_const);


void BM_u32_const(benchmark::State& state) {
  mt19937 gen(42);
  constexpr unsigned mod = 1000'000'007;
  const int N = 1000;
  vector<unsigned> v(N);
  for (auto& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_u32_const);


void BM_i32(benchmark::State& state) {
  mt19937 gen(42);
  volatile int _mod = 1000'000'007;
  int mod = _mod;
  const int N = 1000;
  vector<int> v(N);
  for (int& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (int x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i32);


void BM_i64_const(benchmark::State& state) {
  mt19937_64 gen(42);
  constexpr int64_t mod = 1000'000'000'000'000'003; // it is a prime
  const int N = 1000;
  vector<int64_t> v(N);
  for (auto& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i64_const);


void BM_i64_pow2_const(benchmark::State& state) {
  mt19937_64 gen(42);
  constexpr int64_t mod = 1l << 60;
  const int N = 1000;
  vector<int64_t> v(N);
  for (auto& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i64_pow2_const);


void BM_u64_pow2_const(benchmark::State& state) {
  mt19937_64 gen(42);
  constexpr uint64_t mod = 1l << 60;
  const int N = 1000;
  vector<uint64_t> v(N);
  for (auto& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_u64_pow2_const);


void BM_i64(benchmark::State& state) {
  mt19937_64 gen(42);
  volatile int64_t _mod = 1000'000'000'000'000'003; // it is a prime
  int64_t mod = _mod;
  const int N = 1000;
  vector<int64_t> v(N);
  for (auto& x : v) {
    x = gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i64);


void BM_i128_const(benchmark::State& state) {
  using i128 = __int128;
  mt19937_64 gen(42);
  constexpr i128 mod = 1000'000'000'000'000'003; // it is a prime
  const int N = 1000;
  vector<i128> v(N);
  for (auto& x : v) {
    x = static_cast<i128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i128_const);


void BM_i128(benchmark::State& state) {
  using i128 = __int128;
  mt19937_64 gen(42);
  volatile i128 _mod = 1000'000'000'000'000'003; // it is a prime
  i128 mod = _mod;
  const int N = 1000;
  vector<i128> v(N);
  for (auto& x : v) {
    x = static_cast<i128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i128);


void BM_i128_pow2_const(benchmark::State& state) {
  using i128 = __int128;
  mt19937_64 gen(42);
  constexpr i128 mod = static_cast<i128>(1) << 100;
  const int N = 1000;
  vector<i128> v(N);
  for (auto& x : v) {
    x = static_cast<i128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i128_pow2_const);


void BM_u128_pow2_const(benchmark::State& state) {
  using u128 = __uint128_t;
  mt19937_64 gen(42);
  constexpr u128 mod = static_cast<u128>(1) << 100;
  const int N = 1000;
  vector<u128> v(N);
  for (auto& x : v) {
    x = static_cast<u128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_u128_pow2_const);


void BM_u128_mersenne_const(benchmark::State& state) {
  using u128 = __uint128_t;
  mt19937_64 gen(42);
  constexpr u128 mod = (static_cast<u128>(1) << 89) - 1; // a prime
  const int N = 1000;
  vector<u128> v(N);
  for (auto& x : v) {
    x = static_cast<u128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_u128_mersenne_const);


void BM_u128_mersenne_custom(benchmark::State& state) {
  using u128 = __uint128_t;
  mt19937_64 gen(42);
  constexpr u128 mod = (static_cast<u128>(1) << 89) - 1; // a prime
  const int N = 1000;
  vector<u128> v(N);
  for (auto& x : v) {
    x = static_cast<u128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(remainder(x));
    }
  }
}

BENCHMARK(BM_u128_mersenne_custom);


void BM_u128_mersenne_repeat(benchmark::State& state) {
  using u128 = __uint128_t;
  mt19937_64 gen(42);
  constexpr u128 mod = (static_cast<u128>(1) << 89) - 1; // a prime
  const int N = 1000;
  vector<u128> v(N);
  for (auto& x : v) {
    x = static_cast<u128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(remainder_repeat(x));
    }
  }
}

BENCHMARK(BM_u128_mersenne_repeat);


void BM_u128_mersenne_cmov(benchmark::State& state) {
  using u128 = __uint128_t;
  mt19937_64 gen(42);
  constexpr u128 mod = (static_cast<u128>(1) << 89) - 1; // a prime
  const int N = 1000;
  vector<u128> v(N);
  for (auto& x : v) {
    x = static_cast<u128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(remainder_cmov(x));
    }
  }
}

BENCHMARK(BM_u128_mersenne_cmov);


void BM_i128_pow2(benchmark::State& state) {
  using i128 = __int128;
  mt19937_64 gen(42);
  volatile i128 _mod = static_cast<i128>(1) << 100;
  i128 mod = _mod;
  const int N = 1000;
  vector<i128> v(N);
  for (auto& x : v) {
    x = static_cast<i128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_i128_pow2);


void BM_u128_pow2(benchmark::State& state) {
  using u128 = __uint128_t;
  mt19937_64 gen(42);
  volatile u128 _mod = static_cast<u128>(1) << 100;
  u128 mod = _mod;
  const int N = 1000;
  vector<u128> v(N);
  for (auto& x : v) {
    x = static_cast<u128>(gen()) << 64 | gen();
  }
  for (auto _ : state) {
    for (auto x : v) {
      benchmark::DoNotOptimize(x % mod);
    }
  }
}

BENCHMARK(BM_u128_pow2);


BENCHMARK_MAIN();