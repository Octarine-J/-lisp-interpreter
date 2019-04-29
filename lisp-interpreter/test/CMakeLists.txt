set(
    TESTS
        src/main.cc
        src/parser_test.cc
        src/interpreter_test.cc
        src/expression_test.cpp)

add_executable(tests ${TESTS})

#target_include_directories(tests PUBLIC "../include")
target_link_libraries(tests lisp_interpreter gtest gmock)

