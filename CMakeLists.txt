cmake_minimum_required(VERSION 3.23)
project(labwork_3_Valerochka1337)

set(CMAKE_CXX_STANDARD 14)

include_directories(image)
include_directories(model)
include_directories(parser)
include_directories(bin)

add_subdirectory(image)
add_subdirectory(model)
add_subdirectory(parser)
add_subdirectory(bin)
