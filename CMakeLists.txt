cmake_minimum_required(VERSION 3.30)
project(PracticalWork C)

set(CMAKE_C_STANDARD 23)

add_executable(PracticalWork src/main.c
        #[[TODO Uncomment files if needed]]
        #[[include/antenna.h
        src/antenna_effect.c
        include/antenna_effect.h]]
        src/io_ops.c
        include/io_ops.h
        #[[src/menu.c
        include/menu.h]]
        src/graph.c
        include/graph.h
        src/ui.c
        include/ui.h
        include/strings.h
)

target_compile_definitions(PracticalWork PRIVATE LANG_TR)