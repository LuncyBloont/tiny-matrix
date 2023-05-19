cmake_minimum_required(VERSION 3.10.1)
project(tinymatrix)

include_directories(./)

file(GLOB_RECURSE EXTRA_SOURCE "include/tinymat/*.hpp" "include/tinymat/*.h")

add_executable(main main.cpp ${EXTRA_SOURCE})

target_include_directories(main PRIVATE "include")