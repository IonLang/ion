cmake_minimum_required(VERSION 3.24)
project(ion LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS_LIST})

include_directories(src)

FILE(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/src/*.*)

add_executable(ion ${SRC_LIST})

llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(ion ${llvm_libs})
