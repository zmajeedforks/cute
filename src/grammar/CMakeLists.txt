# cute/grammar/CMakeLists.txt

project(cute_grammar)

find_package(FLEX)
find_package(BISON)

# generated source filename should match .l filename
flex_target(flex_files cute_lexer.flex.l ${CMAKE_CURRENT_BINARY_DIR}/cute_lexer.flex.cpp COMPILE_FLAGS -f)

# generated source filename should match .y filename
bison_target(bison_files cute_parser.bison.y ${CMAKE_CURRENT_BINARY_DIR}/cute_parser.bison.cpp COMPILE_FLAGS "-Wall -Wdangling-alias -Werror --report lookaheads,cex,solved --report-file bisonreport.txt")

add_flex_bison_dependency(flex_files bison_files)

# export to use in cmakefile for standalone parser in different directory
set(CUTE_PARSER_BISON_CPP_FILE ${BISON_bison_files_OUTPUT_SOURCE} CACHE STRING "" FORCE)

add_library(flexbisonlib.cuteparser STATIC ${FLEX_flex_files_OUTPUTS} ${BISON_bison_files_OUTPUT_SOURCE})

target_compile_definitions(flexbisonlib.cuteparser PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(flexbisonlib.cuteparser PRIVATE -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10)
target_compile_options(flexbisonlib.cuteparser PRIVATE $<$<CONFIG:debug>: -O0 -ggdb3> $<$<CONFIG:release>: -Og>)

target_include_directories(flexbisonlib.cuteparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR})

