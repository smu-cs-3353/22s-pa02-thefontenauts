cmake_minimum_required(VERSION 3.20)
project(PA02)

# Create the executable for sorting
add_executable(PA02 src/main.cpp src/FileManager.cpp src/FileManager.h src/DataSet.h src/Algorithms.h)

# Copy the contents of the input folder into build/input
add_custom_command(TARGET PA02 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/input/ $<TARGET_FILE_DIR:PA02>/input/)

