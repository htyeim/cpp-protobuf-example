cmake_minimum_required(VERSION 3.1)

project(protobuf-example)

include_directories(include)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED on)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

execute_process(COMMAND conan install .. --build=missing)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)

find_package(protobuf REQUIRED)

add_subdirectory(src)
add_subdirectory(proto)
