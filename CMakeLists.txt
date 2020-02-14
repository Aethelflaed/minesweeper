cmake_minimum_required(VERSION 3.3)
project(minesweeper)
project(minesweeper_base)

# Global C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

# Conan
include(${CMAKE_BINARY_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(minesweeper_base STATIC src/base/grid.cpp src/base/case.cpp)

add_executable(minesweeper src/main.cpp)
target_link_libraries(minesweeper minesweeper_base)

enable_testing()
add_subdirectory(${CMAKE_BINARY_DIR}/test)
