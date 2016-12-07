cmake_minimum_required(VERSION 3.5)
project(Projet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread ")

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
        src/Point.h
        src/Graph.cpp
        src/Graph.h
        src/SynchroBarrier.cpp
        src/SynchroBarrier.h
        src/Monitor.cpp
        src/Monitor.h
        )
add_executable(Projet ${SOURCE_FILES})


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Projet pthread ${SFML_LIBRARIES})
endif()




