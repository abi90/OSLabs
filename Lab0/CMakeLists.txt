cmake_minimum_required(VERSION 3.6)
project(OSLab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/problem1/tictactoetomek.c)
add_executable(OSLab1 ${SOURCE_FILES})