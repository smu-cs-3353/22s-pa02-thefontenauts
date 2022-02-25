cmake_minimum_required(VERSION 3.15)
project(PA02)
set(CMAKE_CXX_STANDARD 14)

#set (input01 "input/example.txt")

# Copy data files to build dir
#foreach(file IN LISTS input01)
#    configure_file(${file} ${file} COPYONLY)
#endforeach()


# Create the executable for sorting

add_executable(PA02 src/main.cpp)
