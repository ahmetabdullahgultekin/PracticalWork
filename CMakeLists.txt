cmake_minimum_required(VERSION 3.30)
project(PracticalWork C)

set(CMAKE_C_STANDARD 23)

add_executable(PracticalWork main.c
        antenna.c
        antenna.h
        antenna_effect.c
        antenna_effect.h
)
