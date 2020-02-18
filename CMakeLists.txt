cmake_minimum_required(VERSION 3.3)
project(minesweeper)
project(minesweeper_base)

# Global configuration; dir for additional CMake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Build in debug by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  message(WARNING "Setting default CMAKE_BUILD_TYPE to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Global C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags to add (a lot) of warnings
add_compile_options(-Wall -Wextra -pedantic)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Enable coverage
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CodeCoverage)

  if(LCOV_PATH)
    # Append the --coverage flag to compile and link options
    append_coverage_compiler_flags()

    # Exclude source code which we don't want to appear in the source coverage
    set(COVERAGE_EXCLUDES
      # Standard includes are generally located in /usr
      "/usr/*"
      # Conan provides this variable which points to the boost location
      "${CONAN_BOOST_ROOT}/*"
      # The actual test files
      "${CMAKE_SOURCE_DIR}/test/*"
      )

    # Setup coverage using lcov
    # https://github.com/linux-test-project/lcov
    setup_target_for_coverage_lcov(
      NAME coverage
      EXECUTABLE make test
      )
  else()
    message(WARNING "Coverage not enable; install lcov")
  endif()
endif()

# Defines the ./include/ directory as being accessible for includes
# during compilation
include_directories(${CMAKE_SOURCE_DIR}/include)

# First we create a static library for the minesweeper base code.
# This same library will be linked against in the tests.
#
# In this situation, one could also use the special "OBJECT" library
# type provided by CMake, but the syntax to use it would be less readable:
#
#   $<TARGET_OBJECTS:minesweeper_base>
#
# https://cmake.org/cmake/help/v3.0/command/add_library.html
add_library(minesweeper_base STATIC src/base/grid.cpp src/base/case.cpp)

# Add the minesweeper executable itself
add_executable(minesweeper src/main.cpp)

# Link the executable to the base library code we created before
target_link_libraries(minesweeper minesweeper_base)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  enable_testing()

  # Include the test subdirectory to the build
  add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()
