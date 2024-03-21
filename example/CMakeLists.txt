cmake_minimum_required(VERSION 3.28)
project(example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../src)

add_executable(${PROJECT_NAME} src/main.cpp)
