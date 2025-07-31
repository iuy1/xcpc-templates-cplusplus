#include "fft.hpp"
#include "karatsuba.hpp"
#include "ntt.hpp"

#include <benchmark/benchmark.h>

#include <numeric>

template <auto mul>
void BM_poly_mul(benchmark::State& state) {
  vector<ll> a(state.range(0));
  vector<ll> b(state.range(0));
  iota(a.begin(), a.end(), 0);
  iota(b.begin(), b.end(), 0);
  for (auto _ : state) {
    auto r = mul(a, b);
    benchmark::DoNotOptimize(r);
  }
}

BENCHMARK(BM_poly_mul<kara_mul<8>>)->Range(1, 1 << 18)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_poly_mul<kara_mul<16>>)->Range(1, 1 << 18)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_poly_mul<kara_mul<32>>)->Range(1, 1 << 18)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_poly_mul<kara_mul<64>>)->Range(1, 1 << 18)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_poly_mul<fft::fft_mul>)->Range(1, 1 << 20)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_poly_mul<ntt_mul>)->Range(1, 1 << 20)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();