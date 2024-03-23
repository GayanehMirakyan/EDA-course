cmake_minimum_required(VERSION 3.25)
project(EDA_course)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

add_executable(EDA_course
        ./src/main.cpp)
