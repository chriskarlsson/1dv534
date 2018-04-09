cmake_minimum_required(VERSION 2.8)

project(1dv534_1_1_miserable_test)

include_directories(../../../Catch2/single_include/)
include_directories(../src/)
include_directories(./)

add_executable(${PROJECT_NAME} "miserable-test.cpp" "measurements-mock.cpp")

target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_BINARY_DIR}/src/CMakeFiles/1dv534_1_1_miserable.dir/miserable.cpp.obj
)
