cmake_minimum_required(VERSION 3.23)

set(project "lab5")
project(${project} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(MyVector)
add_subdirectory(MySet)

add_executable(${project}
    main.cpp
)

target_link_libraries(${project} PRIVATE
    MySet
    MyVector
)
