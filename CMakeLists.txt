cmake_minimum_required(VERSION 3.21)
project(linked_lists_number_sum)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

add_executable(linked_lists_number_sum main.cpp)
target_link_libraries(linked_lists_number_sum PRIVATE CONAN_PKG::fmt CONAN_PKG::gtest CONAN_PKG::range-v3)

add_test(linked_lists_number_sum linked_lists_number_sum)
