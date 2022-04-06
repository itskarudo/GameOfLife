cmake_minimum_required(VERSION 3.23)

project(GameOfLife)

find_package(Curses REQUIRED)

file(GLOB sources src/*)
add_executable(GameOfLife ${sources})

set_property(TARGET GameOfLife PROPERTY C_STANDARD 90)

target_include_directories(GameOfLife PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(GameOfLife ${CURSES_LIBRARIES})
