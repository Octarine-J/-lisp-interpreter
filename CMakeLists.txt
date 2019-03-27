cmake_minimum_required(VERSION 3.12)
project(lisp_interpretator)

set(CMAKE_CXX_STANDARD 14)

add_executable(lisp_interpretator
        main.cc expressions.cpp expressions.h eval_expressions.cpp eval_expressions.h parse.cpp parse.h)
