cmake_minimum_required(VERSION 2.8)

add_executable(${PROJECT_NAME} "main.cpp" "miserable.cpp" "file-measurements.cpp")

include_directories(./)

configure_file(templog.txt templog.txt COPYONLY)
