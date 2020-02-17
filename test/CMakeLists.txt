# This function takes a file in argument and create a new executable
# using this file and link it to minesweeper_base.
#
# The executable created is also added to the test list, and can simply be run
# by calling `make test`
function(create_test file)
  get_filename_component(test_name ${file} NAME_WE)

  # Append /test to the output directory
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

  add_executable(${test_name} ${file})
  target_link_libraries(${test_name} minesweeper_base)

  add_test(
    NAME ${test_name}
    COMMAND ${test_name}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endfunction()

create_test(test_base_case.cpp)
create_test(test_base_grid.cpp)
