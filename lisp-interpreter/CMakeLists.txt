set(SOURCES
        src/parser/expression.cpp
        src/parser/parser.cpp
        src/interpreter/interpreter.cpp
        src/parser/tokenizer.cpp
)

add_library(lisp_interpreter ${SOURCES})

target_include_directories(lisp_interpreter PUBLIC "include")

install(
    TARGETS lisp_interpreter
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

add_subdirectory(test)

