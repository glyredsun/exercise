cmake_minimum_required(VERSION 3.11)

project(cpp-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(object)
add_subdirectory(lambda)
add_subdirectory(operator_overload)
add_subdirectory(virtual_table)
add_subdirectory(thread)
add_subdirectory(thread_join)
add_subdirectory(call_once)
add_subdirectory(smartptr)
add_subdirectory(new)
