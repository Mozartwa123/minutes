cmake_minimum_required(VERSION 3.16)

project(
        minutes
        VERSION 1.1
        LANGUAGES C
        DESCRIPTION "Tool to summarise youtube statistics")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra -Werror -pedantic")

add_executable( minutes
    main.c
    logs.c
    minutes.c
    minutes_set.c
    intdata.c
    minute_data.c
)