cmake_minimum_required(VERSION 3.7)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./lib)

#add_library(string source/String.cpp)
#add_executable(string )
project(1dv534_2_2_strings)

add_executable(${PROJECT_NAME} "source/String.cpp")

#set_target_properties(string PROPERTIES SUFFIX ".lib")

include_directories(include)
