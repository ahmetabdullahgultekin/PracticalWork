cmake_minimum_required(VERSION 3.30)
project(PracticalWork C)

set(CMAKE_C_STANDARD 23)

add_executable(PracticalWork src/main.c
        src/antenna.c
        src/antenna.h
        src/antenna_effect.c
        src/antenna_effect.h
        src/io_ops.c
        src/io_ops.h
)
