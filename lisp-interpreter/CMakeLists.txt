set(SOURCES
        src/parser/expression.cpp
        src/parser/parser.cpp
        src/interpreter/interpreter.cpp
        src/parser/tokenizer.cpp
        src/interpreter/interpreter_stdlib.cpp
        src/interpreter/args.cpp)

add_library(lisp_interpreter ${SOURCES})

if (MSVC)
    
else()
    SET(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

add_executable(lisp_interpreter_repl src/main.cpp)
target_link_libraries(lisp_interpreter_repl lisp_interpreter)

target_include_directories(lisp_interpreter PUBLIC "include")

install(
    TARGETS lisp_interpreter
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

add_subdirectory(test)

