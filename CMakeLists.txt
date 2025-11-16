cmake_minimum_required(VERSION 3.27)
project(Scratch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Scratch src/main.cpp)

target_include_directories(Scratch  PUBLIC ${CMAKE_SOURCE_DIR}/include)