# cute/lexer/CMakeLists.txt

project(cute_ast)

add_executable(cute_ast.gtest cute_ast.gtest.cpp)

target_compile_definitions(cute_ast.gtest PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(cute_ast.gtest PRIVATE -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10)
target_compile_options(cute_ast.gtest PRIVATE $<$<CONFIG:debug>: -O0 -ggdb3> $<$<CONFIG:release>: -Og>)

target_link_libraries(cute_ast.gtest gmock_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(cute_ast.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

