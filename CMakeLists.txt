cmake_minimum_required(VERSION 3.27)
project(des_cpp)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
add_executable(des_cpp main.cpp)
target_link_libraries(des_cpp PUBLIC des)