cmake_minimum_required(VERSION 2.8.4)
project(NHangMan)

set(SOURCE_FILES main.cpp)
add_executable(NHangMan ${SOURCE_FILES})
target_link_libraries(NHangMan ncurses)