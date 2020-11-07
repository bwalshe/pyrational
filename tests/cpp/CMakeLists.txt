cmake_minimum_required(VERSION 3.5)

find_package(Catch2 REQUIRED)
add_executable(test test_rational.cpp ${CMAKE_SOURCE_DIR}/src/rational.cpp)
target_link_libraries(test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(test)
