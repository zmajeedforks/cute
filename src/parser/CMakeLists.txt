# cute/parser/CMakeLists.txt

project(cute_parser_bison)

# standalone parser
add_executable(cuteparse ${CUTE_PARSER_BISON_CPP_FILE})

target_compile_definitions(cuteparse PRIVATE BUILD_BISON_MAIN)
target_compile_definitions(cuteparse PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(cuteparse PRIVATE -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10)
target_compile_options(cuteparse PRIVATE $<$<CONFIG:debug>: -O0 -ggdb3> $<$<CONFIG:release>: -Og>)

target_link_libraries(cuteparse flexbisonlib.cuteparser)

# tests

add_executable(cute_parser.gtest cute_parser.gtest.cpp)

target_compile_definitions(cute_parser.gtest PRIVATE $<$<PLATFORM_ID:CYGWIN>: GTEST_HAS_PTHREAD=1 _POSIX_C_SOURCE=200809L _GNU_SOURCE>)

target_compile_options(cute_parser.gtest PRIVATE -Wall -Werror -Wextra -std=c++26 -pthread -fconcepts-diagnostics-depth=10)
target_compile_options(cute_parser.gtest PRIVATE $<$<CONFIG:debug>: -O0 -ggdb3> $<$<CONFIG:release>: -Og>)

target_link_libraries(cute_parser.gtest flexbisonlib.cuteparser gmock_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(cute_parser.gtest DISCOVERY_MODE PRE_TEST EXTRA_ARGS --gtest_color=yes)

