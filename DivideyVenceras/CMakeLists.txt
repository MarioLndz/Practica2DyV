cmake_minimum_required(VERSION 3.23)
project(Practica2DyV)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Practica2DyV src/main.cpp include/punto.h src/punto.cpp include/QuickSort.h)
