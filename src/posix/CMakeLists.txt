get_subdirectories(CHILD_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/posix/${child})
message("${Green}-- binary output are in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${ColourReset}")

foreach(child ${CHILD_DIRS})
    message("-- processing ${CMAKE_CURRENT_SOURCE_DIR}/${child}")
    file(GLOB SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${child}/*.c)
    add_executable(${child} ${SOURCES_DIR})
endforeach()
