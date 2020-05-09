cmake_minimum_required(VERSION 3.12)
project(LispInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4 /MT)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

# libraries
add_subdirectory(googletest)

# main project
add_subdirectory(lisp-interpreter)

