add_executable(binary_search_test binary_search_test.cpp)
target_link_libraries(binary_search_test GTest::GTest)
add_test(NAME BinarySearchTest COMMAND binary_search_test)

add_executable(allocator_bench allocator_bench.cpp)
target_link_libraries(allocator_bench benchmark::benchmark)
