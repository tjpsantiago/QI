get_subdirectories(CHILD_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(child ${CHILD_DIRS})
    message("-- processing ${CMAKE_CURRENT_SOURCE_DIR}/${child}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/cpp/${child})
    message("${Green}-- binary output are in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${ColourReset}")
    # add_subdirectory(${child})
endforeach()
