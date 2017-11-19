cmake_minimum_required(VERSION 2.8)

project(miscellaneous_cpp_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(auto_test auto_test.cpp)
#set_target_properties(auto_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

add_executable(lambda_test lambda_test.cpp)

add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test pthread)

add_executable(chrono_test chrono_test.cpp)
