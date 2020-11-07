cmake_minimum_required(VERSION 2.8.12)
project(pyrational)

ADD_COMPILE_OPTIONS("-std=c++17")

file(GLOB SOURCES src/*.cpp)

include_directories(include)
add_subdirectory(extern/pybind11)
add_subdirectory(tests/cpp)
pybind11_add_module(pyrational ${SOURCES})
