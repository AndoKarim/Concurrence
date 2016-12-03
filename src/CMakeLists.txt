cmake_minimum_required(VERSION 3.5.1)
project(src)
find_package( Threads )

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Character.cpp Main.cpp Motor.cpp OptionChecker.cpp Plateau.cpp Point.cpp)

add_executable(src ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
target_link_libraries( src ${CMAKE_THREAD_LIBS_INIT} )
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(src ${SFML_LIBRARIES})
endif()
