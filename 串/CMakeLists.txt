add_executable(kmp_test kmp_test.cpp)
target_link_libraries(kmp_test GTest::GTest)
add_test(NAME KmpTest COMMAND kmp_test)
