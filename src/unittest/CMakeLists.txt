cmake_minimum_required(VERSION 3.0)
project(unittest)

INCLUDE_DIRECTORIES(../core)
add_executable(unittest unittest.cpp)
target_link_libraries(unittest gtest tb armadillo)
