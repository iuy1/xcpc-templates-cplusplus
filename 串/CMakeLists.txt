add_executable(hash_test hash_test.cpp)
target_link_libraries(hash_test GTest::GTest)
add_test(NAME hash_test COMMAND hash_test)

add_executable(kmp_test kmp_test.cpp)
target_link_libraries(kmp_test GTest::GTest)
add_test(NAME kmp_test COMMAND kmp_test)
