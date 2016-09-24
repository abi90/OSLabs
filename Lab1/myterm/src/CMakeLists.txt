cmake_minimum_required(VERSION 2.8)
project(lab1)
set(lab1_sources
shell.cxx
command.h
command.cxx
)
include_directories(/usr/include/boost)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(lab1 ${lab1_sources})
