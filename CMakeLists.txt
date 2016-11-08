project(Lesson1)
add_definitions(-std=c++11)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

file(GLOB SRC_LIST
    *.h
    *.c
    *.hpp
    *.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
