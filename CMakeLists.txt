cmake_minimum_required(VERSION 3.5.1)

project(Table)

include_directories(include)

set(EXECUTABLE_NAME "TableTest")
add_executable(${EXECUTABLE_NAME}
    src/tableTest.cpp
    src/table.cpp)

set(CMAKE_CXX_FLAGS "-g -Wall")

