cmake_minimum_required(VERSION 2.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./lib)

add_library(clock source/Clock.cpp)
add_library(mytime source/MyTime.cpp)

set_target_properties(clock PROPERTIES SUFFIX ".lib")
set_target_properties(mytime PROPERTIES SUFFIX ".lib")

include_directories(include)
