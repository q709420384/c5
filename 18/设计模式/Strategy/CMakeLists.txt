cmake_minimum_required(VERSION 3.10)
project(Strategy)

set(CMAKE_CXX_STANDARD 11)

add_executable(Strategy main.cpp strategy.cpp strategy.h context.h context.cpp)