cmake_minimum_required(VERSION 3.27)
project(AVLTree)

set(CMAKE_CXX_STANDARD 17)



#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

find_package(Catch2 REQUIRED)

include_directories(test-unit)

add_executable(Main main.cpp)

add_executable(Tests test-unit/test.cpp)

target_link_libraries(Tests Catch2::Catch2)