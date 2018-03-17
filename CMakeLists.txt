cmake_minimum_required(VERSION 3.4)

project(QI)

include(colors.cmake)
include(common_functions.cmake)

get_subdirectories(SOURCE_DIRS ${QI_SOURCE_DIR}/src)

foreach(child ${SOURCE_DIRS})
    add_subdirectory(src/${child})
endforeach()
