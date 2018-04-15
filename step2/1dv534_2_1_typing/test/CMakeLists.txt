cmake_minimum_required(VERSION 3.7)

project(1dv534_2_1_typing_test)

include_directories(../../../Catch2/single_include/)
include_directories(../src/)
include_directories(./)

add_executable(${PROJECT_NAME} "compare-test.cpp")

target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_BINARY_DIR}/src/CMakeFiles/1dv534_2_1_typing.dir/compare.cpp.o
)
