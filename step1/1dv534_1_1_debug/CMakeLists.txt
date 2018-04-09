cmake_minimum_required(VERSION 2.8)

project(1dv534_1_1_debug)

add_subdirectory(src)

if (UNIX)
    add_subdirectory(test)

    enable_testing()
    add_test(NAME UnitTests COMMAND ${CMAKE_BINARY_DIR}/test/1dv534_1_1_debug_test)
endif (UNIX)
