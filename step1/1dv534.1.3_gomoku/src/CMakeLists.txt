cmake_minimum_required(VERSION 3.7)

add_executable(${PROJECT_NAME} "main.cpp" "gomoku.cpp")

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
set(GAME_ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../game-engine)

include_directories(./)
include_directories(${LIB_DIR}/include/)
include_directories(${GAME_ENGINE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} "${GAME_ENGINE_DIR}/lib/libtakeFive.lib" "${LIB_DIR}/lib/libmenu.lib")