cmake_minimum_required(VERSION 3.3)
project(minesweeper)
project(minesweeper_base)

# Global C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Defines the ./include/ directory as being accessible for includes
# during compilation
include_directories(${CMAKE_SOURCE_DIR}/include)

# First we create a static library for the minesweeper base code.
# This same library will be linked against in the tests.
#
# In this situation, one could also use the special "OBJECT" library
# type provided by CMake, but the syntax to use it would be less readable:
#
#   $<TARGET_OBJECTS:minesweeper>
#
# https://cmake.org/cmake/help/v3.0/command/add_library.html
add_library(minesweeper_base STATIC src/base/grid.cpp src/base/case.cpp)

# Add the minesweeper executable itself
add_executable(minesweeper src/main.cpp)

# Link the executable to the base library code we created before
target_link_libraries(minesweeper minesweeper_base)

# Includes CTest which enables testing automatically if BUILD_TESTING is set
include(CTest)
if(BUILD_TESTING)
  # If we are building tests, include the test subdirectory to the build
  add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()
