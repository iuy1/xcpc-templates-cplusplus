add_executable(mul_test mul_test.cpp)
target_link_libraries(mul_test GTest::GTest)
add_test(NAME mul_test COMMAND mul_test)

add_executable(mul_bench mul_bench.cpp)
target_link_libraries(mul_bench benchmark::benchmark)

add_executable(mersenne_mod_test mersenne_mod_test.cpp)
target_link_libraries(mersenne_mod_test GTest::GTest)
add_test(NAME mersenne_mod_test COMMAND mersenne_mod_test)

add_executable(mod_bench mod_bench.cpp)
target_link_libraries(mod_bench benchmark::benchmark)

add_executable(modint_test modint_test.cpp)
target_link_libraries(modint_test GTest::GTest)
add_test(NAME modint_test COMMAND modint_test)