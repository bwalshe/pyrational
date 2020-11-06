cmake_minimum_required(VERSION 2.8.12)
project(pyrational)

file(GLOB SOURCES src/*.cpp)

include_directories(include)
add_subdirectory(extern/pybind11)
pybind11_add_module(pyrational ${SOURCES})
