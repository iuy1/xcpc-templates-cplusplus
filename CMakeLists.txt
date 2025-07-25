cmake_minimum_required(VERSION 3.31)
project(xcpc-templates)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
  endif ()
else ()
  add_compile_options(-O2)
endif ()

enable_testing()
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_subdirectory(basic)
add_subdirectory(串)
add_subdirectory(数学)
add_subdirectory(数据结构)
add_subdirectory(树与图)
add_subdirectory(计算几何)
