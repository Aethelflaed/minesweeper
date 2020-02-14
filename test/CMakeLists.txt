function(create_test file)
  get_filename_component(test_name ${file} NAME_WE)

  add_executable(${test_name} ${file})
  target_link_libraries(${test_name} minesweeper_base)

  add_test(
    NAME ${test_name}
    COMMAND ${test_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction()

create_test(test_base_case.cpp)
create_test(test_base_grid.cpp)
