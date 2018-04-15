cmake_minimum_required(VERSION 3.7)

add_executable(${PROJECT_NAME} "main.cpp" "typing.cpp" "compare.cpp")

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)

include_directories(./)
include_directories(${LIB_DIR}/include/)

target_link_libraries(${PROJECT_NAME} "${LIB_DIR}/lib/libclock.lib" "${LIB_DIR}/lib/libmytime.lib")
