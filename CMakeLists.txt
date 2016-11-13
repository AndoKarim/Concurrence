cmake_minimum_required(VERSION 3.5)
project(Projet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Character.cpp
        src/Character.h
        src/Main.cpp
        src/Motor.cpp
        src/Motor.h
        src/OptionChecker.cpp
        src/OptionChecker.h
        src/Plateau.cpp
        src/Plateau.h
        src/Point.cpp
        src/Point.h)

add_executable(Projet ${SOURCE_FILES})
target_link_libraries(Projet pthread)
