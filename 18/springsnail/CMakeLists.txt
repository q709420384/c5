cmake_minimum_required(VERSION 3.10)
project(springsnail)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(springsnail
        config.xml
        conn.cpp
        conn.h
        fdwrapper.cpp
        fdwrapper.h
        log.cpp
        log.h
        main.cpp
        mgr.cpp
        mgr.h
        processpool.h)
