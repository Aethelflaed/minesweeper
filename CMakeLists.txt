cmake_minimum_required(VERSION 3.3)
project(minesweeper)

# Global C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

enable_testing()

include_directories(include/)

add_executable(minesweeper src/main.cpp src/grid.cpp src/case.cpp)

add_test(minesweeper_test minesweeper)
