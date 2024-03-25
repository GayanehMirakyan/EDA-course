cmake_minimum_required(VERSION 3.25)
project(EDA_course)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

include_directories(./include)

add_executable(EDA_course
        ./src/main.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
