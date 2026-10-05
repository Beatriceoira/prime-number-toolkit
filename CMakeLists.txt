cmake_minimum_required(VERSION 3.20)
project(prime_number_toolkit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(prime_toolkit
    src/prime_checker.cpp
    src/prime_generator.cpp
    src/prime_factorization.cpp
    src/prime_analysis.cpp
    src/prime_utils.cpp
)

target_include_directories(prime_toolkit PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(prime_toolkit PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

add_executable(prime-toolkit src/main.cpp)
target_link_libraries(prime-toolkit PRIVATE prime_toolkit)

enable_testing()

find_package(GTest QUIET)

if(GTest_FOUND)
    add_executable(prime-tests tests/test_primes.cpp)
    target_link_libraries(prime-tests PRIVATE prime_toolkit GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(prime-tests)
else()
    message(STATUS "GoogleTest not found. Build will continue without the test target.")
endif()
