cmake_minimum_required(VERSION 3.27)
project(des_cpp)

set(CMAKE_CXX_STANDARD 23)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

add_subdirectory(src)
add_executable(des_cpp main.cpp)
target_link_libraries(des_cpp PUBLIC des)

add_subdirectory(test)