cmake_minimum_required(VERSION 4.0)
project(libmc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(src/libs/protocol)