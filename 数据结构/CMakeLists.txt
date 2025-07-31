add_executable(dsu_test dsu_test.cpp)
target_link_libraries(dsu_test GTest::GTest)
add_test(NAME dsu_test COMMAND dsu_test)

add_executable(fenwick_test fenwick_test.cpp)
target_link_libraries(fenwick_test GTest::GTest)
add_test(NAME fenwick_test COMMAND fenwick_test)

add_executable(segtree_test segtree_test.cpp)
target_link_libraries(segtree_test GTest::GTest)
add_test(NAME segtree_test COMMAND segtree_test)