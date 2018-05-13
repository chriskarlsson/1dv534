# CMakeList.txt : CMake project for 1dv534_3_1_text_handler

cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (My1dv53431texthandler "Texthandler.cpp" "TextTest.cpp")
include_directories(./)

configure_file(Historier.txt Historier.txt COPYONLY)