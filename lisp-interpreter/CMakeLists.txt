set(SOURCES
        src/expression.cpp
        src/parser.cpp
        src/interpreter.cpp
        src/tokenizer.cpp
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

