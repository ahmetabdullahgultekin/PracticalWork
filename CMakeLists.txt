cmake_minimum_required(VERSION 3.30)
project(PracticalWork C)

set(CMAKE_C_STANDARD 23)

add_executable(PracticalWork src/main.c
        src/antenna.c
        include/antenna.h
        src/antenna_effect.c
        include/antenna_effect.h
        src/io_ops.c
        include/io_ops.h
        src/menu.c
        include/menu.h
        src/graph.c
        include/graph.h
        src/lang.c
        include/lang.h
        src/ui.c
)
