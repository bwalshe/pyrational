cmake_minimum_required(VERSION 3.5)
project(pyrational)

ADD_COMPILE_OPTIONS("-std=c++17")

file(GLOB SOURCES src/*.cpp)

include_directories(include)
add_subdirectory(extern/pybind11)
pybind11_add_module(pyrational ${SOURCES})

find_package(Catch2 REQUIRED)
include(Catch)
add_executable(unit_tests tests/cpp/test_rational.cpp src/rational.cpp)
target_link_libraries(unit_tests Catch2::Catch2)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(unit_tests)