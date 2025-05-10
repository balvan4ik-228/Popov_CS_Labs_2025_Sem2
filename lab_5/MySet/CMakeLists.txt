cmake_minimum_required(VERSION 3.23)

set(project "MySet")
project(${project} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(${project}_HEADERS
    MySet.h
    MySet.cpp
)

add_library(${project} INTERFACE)
target_include_directories(${project} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(${project} INTERFACE
    ${${project}_HEADERS}
)

target_link_libraries(${project} INTERFACE
    MyVector
)
