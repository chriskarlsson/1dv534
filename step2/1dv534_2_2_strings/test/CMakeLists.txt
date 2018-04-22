cmake_minimum_required(VERSION 3.7)

project(1dv534_2_2_strings_test)

add_executable(${PROJECT_NAME} "Test2_2.cpp")

target_link_libraries(
    ${PROJECT_NAME}
    ${CMAKE_BINARY_DIR}/string/CMakeFiles/string.dir/source/String.cpp.o
)


set(STRING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../string)

include_directories(${STRING_DIR}/include/)

#target_link_libraries(${PROJECT_NAME} "${STRING_DIR}/lib/libstring.lib")
