cmake_minimum_required(VERSION 2.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./lib)

add_library(takeFive source/TakeFive.cpp)

set_target_properties(takeFive PROPERTIES SUFFIX ".lib")

include_directories(include)
