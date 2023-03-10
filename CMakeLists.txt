cmake_minimum_required(VERSION 3.10.1)
project(tinymatrix)

include_directories(./)

set(EXTRA_SOURCE 
    __vec_func.hpp
    __vec_func2.hpp
    __vec_func3.hpp
    __vec_op.hpp
    __vec_type.hpp
    matrix.hpp
    mat_func.hpp
    mat2str.hpp)

add_executable(main main.cpp ${EXTRA_SOURCE})

