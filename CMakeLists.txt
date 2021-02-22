cmake_minimum_required(VERSION 3.17)
project(quickProblem)

set(CMAKE_CXX_STANDARD 14)

add_executable(quickProblem main.cpp BinHeap.cpp BinHeap.h Service.cpp Service.h)