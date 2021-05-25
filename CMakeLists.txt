cmake_minimum_required(VERSION 3.19)
project(seahash C)

set(CMAKE_C_STANDARD 99)
if (TARGET32)
    add_compile_definitions(TARGET32BIT)
    else()
    add_compile_definitions(TARGET64BIT)
endif ()

include_directories(include)
add_library(cseahash SHARED src/seahash.c include/seahash.h)
add_library(cseahash-static src/seahash.c include/seahash.h)
# Metal is intended for use in embedded/os level applications
add_library(cseahash-metal src/seahash.c include/seahash.h)
add_executable(test test/test.c)
target_compile_options(cseahash-metal PUBLIC -ffreestanding -nostdlib -static -mno-red-zone --target=elf-x86_64)
target_link_libraries(test cseahash-static)
