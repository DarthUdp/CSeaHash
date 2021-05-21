cmake_minimum_required(VERSION 3.19)
project(seahash C)

set(CMAKE_C_STANDARD 99)
if (TARGET32)
    add_compile_definitions(TARGET32BIT)
    else()
    add_compile_definitions(TARGET64BIT)
endif ()

add_library(seahash SHARED src/seahash.c include/seahash.h)
add_library(seahash-static src/seahash.c include/seahash.h)