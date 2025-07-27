#include "allocator.hpp"

#include <benchmark/benchmark.h>

#include <list>
#include <memory_resource>
#include <vector>
#include <numeric>
#include <random>
#include <ranges>
#include <span>


using namespace std;

// insert [0,n) to a list and erase them at a random order

class EraseOrder : public benchmark::Fixture {
public:
  vector<int> order;

  void SetUp(const benchmark::State& state) override {
    size_t size = state.range(0);
    order.resize(size);
    iota(order.begin(), order.end(), 0);
    mt19937_64 rng(size);
    ranges::shuffle(order, rng);
  }

  void TearDown(const benchmark::State&) override {
    order.clear();
    order.shrink_to_fit();
  }
};


void bench(auto list, span<int const> order) {
  vector<decltype(list.begin())> v(order.size());
  for (auto i : ranges::iota_view(0u, order.size())) {
    v[i] = list.insert(list.end(), i);
  }
  for (auto i : order) {
    list.erase(v[i]);
  }
}


BENCHMARK_DEFINE_F(EraseOrder, std_allocator)(benchmark::State& state) {
  for (auto _ : state) {
    bench(list<int>{}, this->order);
  }
}

BENCHMARK_REGISTER_F(EraseOrder, std_allocator)->Range(1, 1 << 20)->Unit(
    benchmark::kMillisecond);


BENCHMARK_DEFINE_F(EraseOrder,  synchronized_pool_resource)(benchmark::State& state) {
  for (auto _ : state) {
    pmr:: synchronized_pool_resource mbr;
    bench(pmr::list<int>{pmr::polymorphic_allocator<int>{&mbr}}, this->order);
  }
}

BENCHMARK_REGISTER_F(EraseOrder,  synchronized_pool_resource)->Range(1, 1 << 20)->Unit(
    benchmark::kMillisecond);


BENCHMARK_DEFINE_F(EraseOrder, unsynchronized_pool_resource)(benchmark::State& state) {
  for (auto _ : state) {
    pmr::unsynchronized_pool_resource mbr;
    bench(pmr::list<int>{pmr::polymorphic_allocator<int>{&mbr}}, this->order);
  }
}

BENCHMARK_REGISTER_F(EraseOrder, unsynchronized_pool_resource)->Range(1, 1 << 20)->Unit(
    benchmark::kMillisecond);


BENCHMARK_DEFINE_F(EraseOrder, monotonic_buffer_resource)(benchmark::State& state) {
  for (auto _ : state) {
    pmr::monotonic_buffer_resource mbr;
    bench(pmr::list<int>{pmr::polymorphic_allocator<int>{&mbr}}, this->order);
  }
}

BENCHMARK_REGISTER_F(EraseOrder, monotonic_buffer_resource)->Range(1, 1 << 20)->Unit(
    benchmark::kMillisecond);


BENCHMARK_DEFINE_F(EraseOrder, custom_alloc)(benchmark::State& state) {
  for (auto _ : state) {
    alloc<int>::reset();
    bench(list<int, alloc<int> >{}, this->order);
  }
}

BENCHMARK_REGISTER_F(EraseOrder, custom_alloc)->Range(1, 1 << 20)->Unit(
    benchmark::kMillisecond);


BENCHMARK_MAIN();