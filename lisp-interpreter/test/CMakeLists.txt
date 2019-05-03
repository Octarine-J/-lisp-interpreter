set(TESTS
        src/main.cpp
        src/parser/parser_test.cpp
        src/interpreter/interpreter_test.cpp
        src/parser/tokenizer_test.cpp
        src/parser/expression_test.cpp
        src/parser/tree_test.cpp
)

add_executable(tests ${TESTS})

#target_include_directories(tests PUBLIC "../include")
target_link_libraries(tests lisp_interpreter gtest gmock)

