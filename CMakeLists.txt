cmake_minimum_required(VERSION 3.1)

project(kr1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(qq main.cpp autotest.cpp num.cpp hh.h matr.h list.h)
