cmake_minimum_required(VERSION 3.20)
project(PA02)

set(CMAKE_CXX_STANDARD 14)

add_executable(PA02 src/main.cpp)

add_custom_command(TARGET PA02 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/input/ $<TARGET_FILE_DIR:PA02>)
